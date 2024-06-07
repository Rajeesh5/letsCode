#include <execinfo.h>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>
#include <typeinfo>

#include "app_manager.hpp"
#include "plugin_interface.hpp"
#include "thread_sleep.hpp"

using namespace com::bosch::itrams_gen2e;

// #define DEFAULT_INACTIVE_TIME 10L  // 10 minutes
#define THEAD_SLEEP_TIME 10000L  // 10 seconds

static std::atomic<int> signal_value;             // Catch fault type.
static std::atomic<bool> abort_flag{false};       // abort flag
static itrams_gen2e::ThreadSleep main_thd_sleep;  // Thread sleep

// Function to print a backtrace-like hint
void printBacktraceToFile(const std::string& filename, int type) {
  std::ofstream logFile(filename.c_str());

  if (!logFile.is_open()) {
    std::cout << "Error opening log file: " << filename << '\n';
    return;
  }

  logFile << "Backtrace-like hint:\n";
  logFile << "Signal Handler Called : " << type << "\n";

  // Adjust the depth based on the needs
  const int depth = 10;

  void* callstack[depth];
  int frames = backtrace(callstack, depth);

  char** symbols = backtrace_symbols(callstack, frames);

  if (symbols != nullptr) {
    for (int i = 1; i < frames; ++i) {
      logFile << "Frame " << i << ": " << symbols[i] << '\n';
      // may need platform-specific symbol resolution here
    }
    free(symbols);
  }
  logFile.close();
}

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void SignalCallbackHandler(int signal) {
  // send abort signal to main thread
  std::cout << "[MainApp] - Caught signal handler - " << signal << std::endl;
  printBacktraceToFile("./tsw_error.log", signal);
  if ((signal == SIGSEGV) || (signal == SIGILL) || (signal == SIGFPE)) {
    std::exit(EXIT_FAILURE);
    return;
  }

  signal_value = signal;
  abort_flag = true;
  main_thd_sleep.Abort();
}

void UncaughtExceptionHandler() {
  // send abort signal to main thread
  std::cout << "[MainApp] - Unknown Exceptions" << std::endl;
  printBacktraceToFile("./tsw_error.log", _NSIG);
  signal_value = _NSIG;
  abort_flag = true;
  main_thd_sleep.Abort();
}

int main(int argc, char* argv[]) {
  // Inactive time
  // uint32_t inactiveTime = DEFAULT_INACTIVE_TIME;
  // Register Signal
  std::signal(SIGINT, SignalCallbackHandler);   // Ctrl+C
  std::signal(SIGTERM, SignalCallbackHandler);  // Termination signal
  std::signal(SIGSEGV, SignalCallbackHandler);  // Segmentation fault
  std::signal(SIGILL, SignalCallbackHandler);   // Illegal instruction fault
  std::signal(SIGFPE, SignalCallbackHandler);   // Floating point exception
  std::signal(SIGHUP, SignalCallbackHandler);   // Hang-up

  std::set_unexpected(UncaughtExceptionHandler);  // Register uncaught exception

  // Doing some async work.

  appmgr::AppManager& app_manager = appmgr::AppManager::GetInstance();
  app_manager.Start();

  while (true) {
    if (abort_flag) {
      std::cout << "[MainApp] Caught signal Interrupt - "
                << std::to_string(signal_value) << std::endl;
      break;
    }
    main_thd_sleep.Sleep(THEAD_SLEEP_TIME);
  }

  app_manager.RemoveAllPlugins();
  std::cout << "Final END" << std::endl;
}