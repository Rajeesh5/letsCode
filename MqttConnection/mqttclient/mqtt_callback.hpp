#include <mqtt/async_client.h>

class MqttCallback : public mqtt::callback {
  void connection_lost(const std::string &cause) override {
    std::cout << "\nConnection lost" << std::endl;
    if (!cause.empty()) std::cout << "cause: " << cause << std::endl;
  }

  void message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message arrived" << std::endl;
    std::cout << "\tTopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tPayload: '" << msg->to_string() << "'" << std::endl;
  }

  void delivery_complete(mqtt::delivery_token_ptr token) override {
    std::cout << "Delivery complete for token: "
              << (token ? token->get_message_id() : -1) << std::endl;
  }
};
