#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <random>
using namespace std;

class PeriodicTaskRunner {
public:
    PeriodicTaskRunner(std::function<void()> task, std::chrono::milliseconds interval)
        : task(task), interval(interval), stopFlag(false) {}

    void start() {
        thread = std::thread([this] {
            while (!stopFlag) {
                task(); // Execute the task

                // Sleep for the specified interval
                std::this_thread::sleep_for(interval);
            }
        });
    }

    void stop() {
        stopFlag = true;
        if (thread.joinable()) {
            thread.join();
        }
    }

private:
    std::function<void()> task;
    std::chrono::milliseconds interval;
    std::thread thread;
    bool stopFlag;
};




void GenerateRandNbr() {
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

    std::cout << "Random number between " << min << " and " << max << ": " << randomNum << std::endl;
}




int main() {
    // Define the task you want to run periodically
    std::function<void()> myTask = []() {

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::cout << "Task executed at " << std::ctime(&now_time_t) << std::endl;
    };

    // Create a PeriodicTaskRunner with a 1-second interval
    PeriodicTaskRunner taskRunner(myTask, std::chrono::seconds(1));
    PeriodicTaskRunner taskRandom(GenerateRandNbr, std::chrono::seconds(1));

    // Start the periodic task
    taskRunner.start();
    taskRandom.start();

    // Sleep for a while to allow the task to run
    std::this_thread::sleep_for(std::chrono::seconds(60));

    // Stop the task runner
    taskRunner.stop();
    taskRandom.stop();

    return 0;
}
