#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <random>
#include <vector>
using namespace std;

class Runnable {
public:
    virtual void run() =0;
};

class RandomNbrGenerator : public Runnable {
public:

    RandomNbrGenerator(std::vector<int> &numbers):m_number(numbers){}

    void run () {
        // Seed the random number generator
        std::random_device rd;
        std::mt19937 mt(rd());

        // Define a range
        int min = 1;
        int max = 100;

        // Create a distribution
        std::uniform_int_distribution<int> dist(min, max);

        // Generate a random number
        int randomNum = dist(mt);
        m_number.emplace_back(randomNum);
        std::cout << "Random number between " << min << " and " << max << ": " << randomNum << std::endl;
    }
private:
    std::vector<int> m_number;
};

class SysClockGenerator : public Runnable {

public:
    SysClockGenerator(std::vector<string> &buffer): m_buffer(buffer){}

    void run() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // Convert the time_point to a time_t (if needed)
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::cout << "Current time: " << std::ctime(&now_time_t) ;
        m_buffer.push_back(std::ctime(&now_time_t));
    }
private:
    std::vector<string> m_buffer;
};

class CycleThread {
public:
    CycleThread(Runnable *task, std::chrono::milliseconds interval)
        : m_pInstance(task), interval(interval), stopFlag(false) {}

    void start() {
        m_thread = std::thread([this] {
            while (!stopFlag) {
                m_pInstance->run(); // Execute the task

                // Sleep for the specified interval
                std::this_thread::sleep_for(interval);
            }
        });
    }

    void stop() {
        stopFlag = true;
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

private:
    std::chrono::milliseconds interval;
    std::thread m_thread;               // Real thread, and added API arround it.
    Runnable *m_pInstance;
    bool stopFlag;
};


int main() {

    vector<int> randomNumberReadings;           // This maybe our buffer
    vector<string> sysClockReadings;            // This maybe our buffer

    RandomNbrGenerator randomNbrCollector(randomNumberReadings);        // our collectors
    SysClockGenerator sysClockCollector(sysClockReadings);              // our collectors


    CycleThread cycle_th1(&randomNbrCollector,std::chrono::milliseconds(1000));    // Cyclic executor with interval
    CycleThread cycle_th2(&sysClockCollector, std::chrono::milliseconds(500));     // Cyclic executor with interval


    // Start the periodic task
    cycle_th1.start();
    cycle_th2.start();

    // Sleep for a while to allow the task to run
    std::this_thread::sleep_for(std::chrono::seconds(60));

    // Stop the task runner
    cycle_th1.stop();
    cycle_th2.stop();

    return 0;
}
