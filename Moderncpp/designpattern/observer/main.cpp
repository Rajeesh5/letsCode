#include "SpreadsheetModel.hpp"
#include "Views.hpp"

int main() {
  /*
SpreadsheetModel spreadsheetModel{};

ObserverPtr observer1 = std::make_shared<TableView>(spreadsheetModel);
spreadsheetModel.addObserver(observer1);

ObserverPtr observer2 = std::make_shared<BarChartView>(spreadsheetModel);
spreadsheetModel.addObserver(observer2);
spreadsheetModel.changeCellValue("A", 1, 42);
spreadsheetModel.removeObserver(observer1);
spreadsheetModel.changeCellValue("B", 2, 23.1);

ObserverPtr observer3 = std::make_shared<PieChartView>(spreadsheetModel);
spreadsheetModel.addObserver(observer3);
spreadsheetModel.changeCellValue("C", 3, 3.1415926);
*/
  auto model = std::make_shared<SpreadsheetModel>();

  auto tableView = std::make_shared<TableView>(*model);
  auto barChartView = std::make_shared<BarChartView>(*model);
  auto pieChartView = std::make_shared<PieChartView>(*model);

  model->addObserver(tableView);
  model->addObserver(barChartView);
  model->addObserver(pieChartView);

  model->changeCellValue("A", 1, 42.0);
  model->changeCellValue("B", 2, 84.0);

  model->removeObserver(tableView);

  model->changeCellValue("A", 1, 100.0);

  return 0;
}