#include <thread>

#include "mqtt_publisher.hpp"

void SendPackets(MqttPublisher &publisher) {
  // Initialize an empty message with specified topic.
  mqtt::message_ptr message = mqtt::make_message(TOPIC, "");

  // Create a loop for counting down from N seconds.
  for (int i = 10; i > 0; --i) {
    // Configure Mqtt message to contain payload specifying time until end.
    message->set_payload(PAYLOAD + " Time Left: " + std::to_string(i));

    // Enqueue the message to be published.
    publisher.EnqueueMessage(message);

    // Publish the Mqtt message using the connected client.
    int rc = publisher.TryPublish(message);
    if (rc != 0) {
      std::cerr << "Failed to publish message" << std::endl;
      break;
    }
    // Sleep for one second.
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
}

int main() {
  MqttPublisher publisher;
  try {
    publisher.Connect();
    publisher.Subscribe();
    publisher.Start();

    std::thread t1(SendPackets, std::ref(publisher));

    if (t1.joinable()) {
      t1.join();
    }

    publisher.Disconnect();
  } catch (const std::exception &exc) {
    std::cerr << exc.what() << std::endl;
    return 1;
  }
  return 0;
}