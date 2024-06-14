#include "customer.hpp"
#include "order.hpp"

void PrintOrder(const std::shared_ptr<Order>& order) {
  std::cout << "Order ID: " << order->getId();
  std::cout << " with Customer: " << order->getCustomer()->getName()
            << std::endl;
}
int main() {
  // Creating instance of customer
  auto customer1 = std::make_shared<Customer>("Alice");

  // Creating instances of orders
  auto order1 = std::make_shared<Order>(1, customer1);
  auto order2 = std::make_shared<Order>(2, customer1);

  // Adding orders to the customer
  customer1->addOrder(order1);
  customer1->addOrder(order2);

  // Display orders for customer1
  customer1->printOrders();
  PrintOrder(order1);

  return 0;
}
