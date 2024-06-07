#include <iostream>

struct Node {
  Node(int val) : data(val) {}
  int data;
  Node *next;
};

void print_list(Node *head) {
  while (head) {
    std::cout << head->data << "->";
    head = head->next;
  }
  std::cout << "nullptr" << std::endl;
}

Node *newHead;
Node *rev_list(Node *head) {
  if (head == nullptr || head->next == nullptr) {
    newHead = head;
    return head;
  }
  Node *nextNode = head->next;

  head->next = nullptr;
  Node *node = rev_list(nextNode);
  nextNode->next = head;
  node = head;
  return node;
}

// write a code to find the prime number
// 1. 2, 3, 5, 7, 11, 13, 17, 19, 23, 29

int main() {
  Node *head = new Node(10);
  head->next = new Node(20);
  head->next->next = new Node(30);
  head->next->next->next = new Node(40);
  head->next->next->next->next = new Node(50);
  head->next->next->next->next->next = nullptr;

  print_list(head);

  rev_list(head);

  print_list(newHead);
}
