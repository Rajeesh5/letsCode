#include "thread_sleep.hpp"

namespace itrams_gen2e {

// Implementation of the Abort function
void ThreadSleep::Abort() {
  {
    std::lock_guard<std::mutex> lock(sleep_mutex);
    abort_flag = true;
    // Notify waiting threads before changing state
    sleep_condition.notify_all();
  }
}

// Implementation of the Sleep function with a timeout
void ThreadSleep::Sleep(uint64_t timeout) {
  std::unique_lock<std::mutex> lock(sleep_mutex);
  // Use lock object for both waiting and checking condition
  sleep_condition.wait_for(lock, std::chrono::milliseconds(timeout),
                           [this] { return abort_flag; });
  abort_flag = false;  // Clear abort flag
}

// Implementation of the Sleep function without a timeout
void ThreadSleep::Sleep() {
  std::unique_lock<std::mutex> lock(sleep_mutex);
  // Use lock object for both waiting and checking condition
  sleep_condition.wait(lock, [this] { return abort_flag; });
  abort_flag = false;  // Clear abort flag
}

}  // namespace itrams_gen2e
