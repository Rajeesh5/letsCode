#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <vector>
#include <map>

class PeriodicTaskRunner {
public:
    PeriodicTaskRunner() : running_(false) {}

    void addNotifyListener(std::function<void()> listener, std::chrono::milliseconds interval) {
        listeners_[listener] = interval;
    }

    void removeListener(std::function<void()> listener) {
        auto it = listeners_.find(listener);
        if (it != listeners_.end()) {
            listeners_.erase(it);
        }
    }

    void start() {
        running_ = true;
        while (running_) {
            // Notify listeners
            for (const auto& entry : listeners_) {
                const auto& listener = entry.first;
                const auto& interval = entry.second;
                listener();
                std::this_thread::sleep_for(interval);
            }
        }
    }

    void stop() {
        running_ = false;
    }

    void stopListener(std::function<void()> listener) {
        auto it = listeners_.find(listener);
        if (it != listeners_.end()) {
            listeners_.erase(it);
        }
    }

    void startListener(std::function<void()> listener, std::chrono::milliseconds interval) {
        listeners_[listener] = interval;
    }

private:
    bool running_;
    std::map<std::function<void()>, std::chrono::milliseconds> listeners_;
};

int main() {
    PeriodicTaskRunner timer;

    // Add listeners with different intervals
    std::function<void()> listener1 = []() {
        std::cout << "Listener 1 notified with 1-second interval." << std::endl;
    };

    std::function<void()> listener2 = []() {
        std::cout << "Listener 2 notified with 2-second interval." << std::endl;
    };

    timer.addNotifyListener(listener1, std::chrono::seconds(1));
    timer.addNotifyListener(listener2, std::chrono::seconds(2));

    // Start the periodic task
    std::thread timerThread([&timer] { timer.start(); });

    // Sleep for a while to allow the listeners to be notified
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Stop listener1 individually
    timer.stopListener(listener1);

    // Sleep for a while
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Start listener1 with a different interval
    timer.startListener(listener1, std::chrono::seconds(3));

    // Sleep for a while
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop the periodic task and the remaining listeners
    timer.stop();
    timerThread.join();

    return 0;
}
