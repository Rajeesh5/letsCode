#include <mqtt/async_client.h>

#include <iostream>
#include <mutex>
#include <queue>
#include <string>

#include "mqtt_action_listner.hpp"
#include "mqtt_callback.hpp"

const std::string BROKER_ADDRESS("tcp://localhost:8883");
const std::string CLIENT_ID("mqtt_publisher");
const std::string TOPIC("test/topic");
const std::string PAYLOAD("Hello MQTT!");

class MqttPublisher {
 public:
  MqttPublisher();
  void Connect(void) const;
  void Subscribe(void) const;
  void Disconnect(void) const;
  int TryPublish(mqtt::message_ptr message) const;
  void OnPublish(bool result, const std::string &received_topic) const;
  void EnqueueMessage(mqtt::message_ptr &message);
  void Start();

 private:
  std::unique_ptr<mqtt::async_client> mqtt_client_ = nullptr;
  mqtt::connect_options connOpts_;
  MqttCallback cb_;
  std::unique_ptr<ActionListener> delivery_listener_;
  std::mutex mqtt_msg_q_mutex_;
  std::queue<mqtt::message_ptr> mqtt_msg_q_;  // MAX 50 msg store.

  std::thread publisher_thread_;
  bool stop_execution_ = false;
};

void MqttPublisher::OnPublish(bool result,
                              const std::string &received_topic) const {
  if (result)
    std::cout << "Delivery completed for " + received_topic + "\n";
  else
    std::cout << "Delivery failed for " + received_topic + "\n";
}

MqttPublisher::MqttPublisher() {
  mqtt_client_ =
      std::make_unique<mqtt::async_client>(BROKER_ADDRESS, CLIENT_ID);
  mqtt_client_->set_callback(cb_);
  connOpts_.set_keep_alive_interval(20);
  connOpts_.set_clean_session(true);

  delivery_listener_ = std::make_unique<ActionListener>("Delivery Listener");

  delivery_listener_->OnActionDone(
      [this](bool result, const std::string &topic) {
        this->OnPublish(result, topic);
      });

  // why not this :
  // delivery_listener_->OnActionDone([this](auto result, auto topic) {
  //   this->OnPublish(std::move(result), std::move(topic));
  // });
  //
  // Explanation
  //
  // Capture by Reference vs. Capture by Move: In the lambda [this](bool result,
  // const std::string& topic), you capture this by value (which is effectively
  // a pointer). This is correct for capturing member functions. If result and
  // topic are passed by value, they don’t need to be captured; they are
  // parameters to the lambda.
  //
  // Moving Objects into Closures: If you needed to capture and move objects,
  // you'd use the C++14 init capture like [obj = std::move(obj)]. However, in
  // your current lambda, there is no object that needs to be moved into the
  // closure.
  //
  // Avoid Unnecessary Copies: Ensure that the parameters to the lambda are
  // passed in the most efficient way. In this case, bool result is cheap to
  // copy, and const std::string& topic avoids copying the string.
  //
  // Summary
  //
  // Your lambda capture in the OnActionDone callback is appropriate for the use
  // case, as you are capturing this to access the member function OnPublish.
  // The parameters bool result and const std::string& topic are handled
  // efficiently. There’s no need for init capture in this specific case since
  // you’re not moving any objects into the closure.
}

void MqttPublisher::Connect(void) const {
  try {
    // Connect to the broker
    std::cout << "Connecting to the MQTT broker..." << std::endl;
    mqtt_client_->connect(connOpts_)->wait();

  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    throw;
  }
}

void MqttPublisher::Subscribe(void) const {
  try {
    // Subscribe to the topic
    std::cout << "Subscribing to topic..." << std::endl;
    mqtt_client_->subscribe(TOPIC, 0)->wait();
  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    throw;
  }
}

void MqttPublisher::Disconnect(void) const {
  try {
    // Disconnect from the broker
    std::cout << "Disconnecting from the MQTT broker..." << std::endl;
    mqtt_client_->disconnect()->wait();
    std::cout << "Disconnect Done." << std::endl;
  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    throw;
  }
}

int MqttPublisher::TryPublish(mqtt::message_ptr message) const {
  try {
    std::cout << "MqttPublisher : publishing mqtt message\n";

    // mqtt_client_->publish(message);
    mqtt_client_->publish(message, nullptr, *delivery_listener_);

  } catch (const mqtt::exception &e) {
    std::cout << "Error when sending mqtt message: " + e.to_string();
  }
  return 0;
}

void MqttPublisher::EnqueueMessage(mqtt::message_ptr &message) {
  std::unique_lock<std::mutex> lock(mqtt_msg_q_mutex_);
  if (mqtt_msg_q_.size() >= 50) {
    std::cout << "Message queue is full, dropping message\n";
    // Here will go the logic to message persister
    return;
  } else {
    mqtt_msg_q_.push(std::move(message));
  }
}

void MqttPublisher::Start() {
  std::cout << "MqttPublisher::Start\n";

  // Can we syncronize it using cv?
  publisher_thread_ = std::thread([this]() {
    while (!stop_execution_) {
      std::unique_lock<std::mutex> lock(mqtt_msg_q_mutex_);
      if (!mqtt_msg_q_.empty()) {
        auto message = std::move(mqtt_msg_q_.front());
        mqtt_msg_q_.pop();
        lock.unlock();
        TryPublish(message);
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });
}