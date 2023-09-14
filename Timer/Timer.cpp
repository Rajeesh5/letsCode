#include <iostream>
#include <atomic>
#include <algorithm>

#include "ThreadPool.h"


class Timer {
public:
    static const int PERIODICAL_TIMER = 1;
    static const int ONE_SHOT_TIMER_NO_DELAY = 2;

    Timer(size_t numThreads) : running_(false), threadPool_(numThreads) {}

    void addNotifyListener(TimerListener* listener, int timerType, long periodMillis, int event) {
        std::unique_lock<std::mutex> lock(mutex_);
        listeners_.emplace_back(listener, timerType, periodMillis, event);

        if (!running_) {
            running_ = true;
            timerThread_ = std::thread([this]() {
                while (running_) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                    std::unique_lock<std::mutex> lock(mutex_);
                    for (auto& info : listeners_) {
                        if (info.timerType == PERIODICAL_TIMER ||
                            (info.timerType == ONE_SHOT_TIMER_NO_DELAY && !info.fired)) {
                            info.fired = true;
                            threadPool_.enqueue(info.listener, info.event);
                        }
                    }
                }
            });
        }
    }

    void removeListener(TimerListener* listener, int event) {
        std::unique_lock<std::mutex> lock(mutex_);
        listeners_.erase(
            std::remove_if(listeners_.begin(), listeners_.end(),
                [&](const ListenerInfo& info) {
                    return info.listener == listener && info.event == event;
                }),
            listeners_.end()
        );
    }

    void start() {
        if (!running_) {
            running_ = true;
            timerThread_ = std::thread([this]() {
                while (running_) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                    std::unique_lock<std::mutex> lock(mutex_);
                    for (auto& info : listeners_) {
                        if (info.timerType == PERIODICAL_TIMER ||
                            (info.timerType == ONE_SHOT_TIMER_NO_DELAY && !info.fired)) {
                            info.fired = true;
                            threadPool_.enqueue(info.listener, info.event);
                        }
                    }
                }
            });
        }
    }

    void stop() {
        if (running_) {
            running_ = false;
            timerThread_.join();
        }
    }

private:
    struct ListenerInfo {
        TimerListener* listener;
        int timerType;
        long periodMillis;
        int event;
        bool fired;

        ListenerInfo(TimerListener* l, int t, long p, int e)
            : listener(l), timerType(t), periodMillis(p), event(e), fired(false) {}
    };

    std::vector<ListenerInfo> listeners_;
    std::thread timerThread_;
    std::atomic<bool> running_;
    std::mutex mutex_;
    ThreadPool threadPool_;
};

class Collector1 : public TimerListener {
    public:
    void timer(int event) {
        std::cout << "Inside Collector1" << std::endl;
    }
};

class Collector2 : public TimerListener {
    void timer(int event) {
        std::cout << "Inside Collector2" << std::endl;
    }
};

int main() {
    Timer myTimer(2);

    Collector1 collector1Instance;
    Collector2 collector2Instance;


    // Add listeners and start the timer immediately
    myTimer.addNotifyListener(&collector1Instance, Timer::PERIODICAL_TIMER, 1000, 1);
    myTimer.addNotifyListener(&collector2Instance, Timer::ONE_SHOT_TIMER_NO_DELAY, 50000, 4);

    std::this_thread::sleep_for(std::chrono::seconds(60));

    myTimer.stop();

    return 0;
}
