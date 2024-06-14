#include "customer.hpp"

#include "order.hpp"

Customer::Customer(const std::string& name) : name(name) {}

void Customer::addOrder(const std::shared_ptr<Order>& order) {
  orders.push_back(order);
}

const std::string& Customer::getName() const { return name; }

void Customer::printOrders() const {
  std::cout << name << " has the following orders:" << std::endl;
  for (const auto& order : orders) {
    std::cout << "- Order ID: " << order->getId() << std::endl;
  }
}
