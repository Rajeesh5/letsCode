#ifndef SPREADSHEET_MODEL_HPP
#define SPREADSHEET_MODEL_HPP

#include <iostream>
#include <string>
#include <unordered_map>

#include "Subject.hpp"

class SpreadsheetModel : public Subject {
 public:
  void changeCellValue(std::string_view column, int row, double value) {
    std::string cell = std::string(column) + std::to_string(row);
    data[cell] = value;
    std::cout << "Cell [" << column << ", " << row << "] = " << value
              << std::endl;
    notifyAllObservers();
  }

  double getCellValue(std::string_view column, int row) const {
    std::string cell = std::string(column) + std::to_string(row);
    auto it = data.find(cell);
    if (it != data.end()) {
      return it->second;
    }
    return 0.0;  // Default value if cell is not found
  }

 private:
  std::unordered_map<std::string, double> data;
};

#endif  // SPREADSHEET_MODEL_HPP
