#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Order;  // Forward declaration

class Customer {
 public:
  explicit Customer(const std::string& name);
  void addOrder(const std::shared_ptr<Order>& order);
  const std::string& getName() const;
  void printOrders() const;

 private:
  std::string name;
  std::vector<std::shared_ptr<Order>> orders;
};

#endif  // CUSTOMER_H
