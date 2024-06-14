#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <memory>
#include <string>

class Customer;  // Forward declaration

class Order {
 public:
  Order(int id, const std::shared_ptr<Customer>& customer);
  int getId() const;
  std::shared_ptr<Customer> getCustomer() const;

 private:
  int id;
  std::weak_ptr<Customer> customer;  // Use weak_ptr to avoid cyclic dependency
};

#endif  // ORDER_H
