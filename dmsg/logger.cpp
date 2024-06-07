#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
void WriteToFileWithTimestamp(const std::string& filename,
                              const std::string& message) {
  // Get current time
  time_t now = time(nullptr);
  struct tm* current_time = localtime(&now);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", current_time);

  // Open file in append mode
  std::ofstream outFile(filename, std::ios::app);

  if (!outFile.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  // Write timestamp and message to file
  outFile << "[" << timestamp << "] " << message << std::endl;

  // Close file
  outFile.close();

  std::cout << "Message logged to " << filename << std::endl;
}

void PrintLog(const std::string& message) {
  // Get current time
  time_t now = time(nullptr);
  struct tm* current_time = localtime(&now);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", current_time);

  std::cout << timestamp << " " << message << std::endl;

  // Create log message with timestamp and provided message
  std::string logMessage = "[" + std::string(timestamp) + "] " + message;

  FILE* pipe =
      popen("dmesg | grep -E '^[A-Za-z0-9_]+:|^[a-zA-Z0-9_-]+:.*audit:'", "r");

  if (!pipe) {
    std::cerr << "Error: Unable to open pipe to dmesg\n";
    return;
  }

  FILE* logFile = fopen("kernel_log.txt",
                        "a");  // Append mode to add log without overwriting

  if (!logFile) {
    std::cerr << "Error: Unable to open log file\n";
    pclose(pipe);
    return;
  }

  // Write custom message to log file
  fprintf(logFile, "%s\n", logMessage.c_str());

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    // Write each line of filtered output from dmesg to the log file
    fprintf(logFile, "%s", buffer);
  }

  // Close the pipe and log file
  pclose(pipe);
  fclose(logFile);

  std::cout << "Kernel messages logged to kernel_log.txt\n";
}

void LOG(const std::string& message, const std::string& logLevel = "DEBUG") {
  std::ofstream kmsg("/dev/kmsg");

  if (!kmsg.is_open()) {
    std::cerr << "Error opening /dev/kmsg\n";
    return;
  }

  std::string marker = "APP_MGR";  // Unique marker to identify our messages
  std::string logMessage = marker + " [" + logLevel + "] " + message + "\n";
  kmsg << logMessage;

  kmsg.close();

  // Wait for a short time to allow the message to be written before closing the
  // file
  usleep(10000);  // Sleep for 10 milliseconds
}

int main() {
  LOG("*** This is a debug message only. ***");

  /*
    std::string logMessage = "This is a test log message.";
    PrintLog(logMessage);
    std::string filename = "log.txt";
    std::string message = "This is a test message.";
    WriteToFileWithTimestamp(filename, message);
  */
  return 0;
}
