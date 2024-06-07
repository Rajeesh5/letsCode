#include <math.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using byte = uint8_t;

std::string StringToHexString(const std::string& str) {
  std::string hexString;
  std::ostringstream oss;
  for (char c : str) {
    oss << std::hex << std::setw(2) << std::setfill('0')
        << (int)(unsigned char)c << " ";
    hexString += oss.str() + " ";
  }

  // Remove the trailing space
  if (!hexString.empty()) {
    hexString.pop_back();
  }
  return hexString;
}
std::string ByteArrayToHexString(const std::vector<byte>& vec) {
  std::string hexString;

  for (byte b : vec) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    hexString += ss.str() + " ";
  }
  // Remove the trailing space
  if (!hexString.empty()) {
    hexString.pop_back();
  }

  return hexString;
}

std::vector<byte> GetByteArray(long data, short size) {
  std::vector<byte> bytes(size);

  for (int i = 0; i < size; i++) {
    auto mask = static_cast<long>(255 * std::pow(256, size - i - 1));
    bytes[i] = static_cast<byte>((data & mask) >> (8 * (size - i - 1)));
  }

  return bytes;
}

int main() {
  try {
    std::string value = "1234";

    long telemetryExportIntervalValue = std::stol(value);
    std::cout << telemetryExportIntervalValue << std::endl;
    int intervalLength = 4;
    std::vector<byte> responseData =
        GetByteArray(telemetryExportIntervalValue, (short)intervalLength);

    std::cout << ByteArrayToHexString(responseData) << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
