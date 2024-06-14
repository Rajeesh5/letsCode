#include "order.hpp"

#include "customer.hpp"

Order::Order(int id, const std::shared_ptr<Customer>& customer)
    : id(id), customer(customer) {}

int Order::getId() const { return id; }

std::shared_ptr<Customer> Order::getCustomer() const {
  return customer.lock();  // Convert weak_ptr to shared_ptr
}
