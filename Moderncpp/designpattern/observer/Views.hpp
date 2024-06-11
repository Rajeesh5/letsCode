#ifndef VIEWS_HPP
#define VIEWS_HPP

#include <iostream>

#include "Observer.hpp"
#include "SpreadsheetModel.hpp"

class TableView : public Observer {
 public:
  explicit TableView(SpreadsheetModel& theModel) : model{theModel} {}
  int getId() const noexcept override { return 1; }
  void update() override {
    std::cout << "Update of TableView. Cell [A, 1] = "
              << model.getCellValue("A", 1) << std::endl;
  }

 private:
  SpreadsheetModel& model;
};

class BarChartView : public Observer {
 public:
  explicit BarChartView(SpreadsheetModel& theModel) : model{theModel} {}
  int getId() const noexcept override { return 2; }
  void update() override {
    std::cout << "Update of BarChartView. Cell [B, 2] = "
              << model.getCellValue("B", 2) << std::endl;
  }

 private:
  SpreadsheetModel& model;
};

class PieChartView : public Observer {
 public:
  explicit PieChartView(SpreadsheetModel& theModel) : model{theModel} {}
  int getId() const noexcept override { return 3; }
  void update() override {
    std::cout << "Update of PieChartView. Cell [A, 1] = "
              << model.getCellValue("A", 1) << std::endl;
  }

 private:
  SpreadsheetModel& model;
};

#endif  // VIEWS_HPP
