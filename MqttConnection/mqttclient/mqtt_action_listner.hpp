
#include <functional>

#include "mqtt/async_client.h"

using OnActionDoneCallbackFn = std::function<void(bool, const std::string &)>;

//! @brief Create a ActionListener which receives a callback from the MQTT
//! client when a message delivery has completed.
//!
class ActionListener : public mqtt::iaction_listener {
 public:
  explicit ActionListener(const std::string &name) : name_(name) {}

  //! @brief Register callback to use after an action either fails or completes
  //! successfully

  void OnActionDone(const OnActionDoneCallbackFn &callback) {
    action_done_callback_ = callback;
  }

 private:
  //! @brief This method is invoked when an action fails.
  //!
  void on_failure(const mqtt::token &token) override;

  //! @brief This method is invoked when an action has completed successfully.
  //!
  void on_success(const mqtt::token &token) override;

  OnActionDoneCallbackFn action_done_callback_;
  std::string name_;
};

void ActionListener::on_failure(const mqtt::token &token) {
  std::cout << name_ << " failed!!!\n";

  auto topic = token.get_topics();

  if (topic && !topic->empty()) {
    action_done_callback_(false, (topic->c_arr())[0]);
  }
}

void ActionListener::on_success(const mqtt::token &token) {
  std::cout << name_ << " succeeded :)\n";
  auto topic = token.get_topics();

  if (topic && !topic->empty()) {
    action_done_callback_(true, (topic->c_arr())[0]);
  }
}
