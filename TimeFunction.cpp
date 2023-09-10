#include <iostream>
#include <chrono>

int main() {
    // Get the current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // Convert the time_point to a time_t (if needed)
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Print the current time
    std::cout << "Current time: " << std::ctime(&now_time_t) << std::endl;

    return 0;
}
