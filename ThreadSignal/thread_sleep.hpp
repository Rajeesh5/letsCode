/**
 * ******************************************************************************************************************
 * Copyright (c) BGSW 2023. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as
 * the communication of its contents to others without explicit authorization is
 * prohibited. Offenders will be held liable for the payment of damages. All
 * rights reserved in the event of the grant of a patent, utility model or
 * design.
 * ******************************************************************************************************************
 */
#ifndef THREAD_SLEEP_H
#define THREAD_SLEEP_H

#include <condition_variable>
#include <mutex>

/// @class ThreadSleep
/// @brief Interface class for thread sleep functionality
namespace itrams_gen2e {
class ThreadSleep {
 public:
  // in order to allow construction of derived objects
  ThreadSleep(void) = default;

  /// @brief Destructor
  virtual ~ThreadSleep(void) = default;

  /// @brief Copy constructor
  ThreadSleep(ThreadSleep const &) = delete;

  /// @brief  Move Constructor
  ThreadSleep(ThreadSleep &&) = delete;

  /// @brief Move Assignment Operator
  ThreadSleep &operator=(ThreadSleep &&) & = delete;

  /// @brief Copy Assignment operator
  ThreadSleep &operator=(ThreadSleep const &) & = delete;

  /// @brief Abort any sleeping threads
  void Abort();

  /// @brief Sleep for the specified timeout in milliseconds
  /// @param timeout The timeout in milliseconds
  void Sleep(uint64_t timeout);

  /// @brief Sleep without a timeout
  void Sleep();

 private:
  volatile bool abort_flag;
  std::mutex sleep_mutex;
  std::condition_variable sleep_condition;

};  // class ThreadSleep
}  // namespace itrams_gen2e
#endif  // THREAD_SLEEP_H
