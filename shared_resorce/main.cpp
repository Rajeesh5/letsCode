
#include <iostream>
#include <thread>
#include <memory>
#include <functional>
#include "Person.h"
#include "PersonDb.h"
#include <condition_variable>
#include <mutex>

/*
volatile sig_atomic_t signal_received = 0;
void signal_handler(int signal) {
    if (signal == SIGINT) {
        signal_received = 1;
    }
}
*/

std::condition_variable cv;
std::mutex cv_m;
bool should_exit = false;

std::function<void(int)> sig_handler_closure = nullptr;

void sigHandler(int signal) {
  if (sig_handler_closure) {
    sig_handler_closure(signal);
  }
}
void attachSignalHandler() {
  // Creating lembda to have function that
  // handles specific below signals :

  sig_handler_closure = [&](int signal) {
    switch (signal) {
      case SIGINT:
      case SIGTERM:
      case SIGSEGV:
      case SIGILL:
      case SIGFPE:
      case SIGHUP:
        /* fall through */
        // Clean-up !!! dont worry taken care by deleter
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lk(cv_m);
            should_exit = true; // Set the flag to indicate exit
            cv.notify_one(); // Notify the waiting thread to exit
        }
      default:
        break;
    }
  };

  std::signal(SIGTERM, sigHandler);  // Ctrl+C
  std::signal(SIGINT,  sigHandler);   // Termination signal
  std::signal(SIGSEGV, sigHandler);  // Segmentation fault
  std::signal(SIGILL,  sigHandler);   // Illegal instruction fault
  std::signal(SIGFPE,  sigHandler);   // Floating point exception
  std::signal(SIGHUP,  sigHandler);   // Hang-up
}


int main() {
     //signal(SIGINT, signal_handler);  // Register signal handler for SIGINT

    attachSignalHandler(); // Attach signal handlers

    PersonDB db;
    std::shared_ptr<Person> p1 = std::make_shared<Person>(10,"xyz");
    
    db.AddPerson(p1);
    std::cout << p1.use_count() << std::endl;

    {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, []{ return should_exit; }); // Wait until the exit flag is set

    }


    return 0;
}