// Recursive C++ program to reverse
// a linked list
#include <iostream>
using namespace std;

/* Link list node */
struct Node {
	int data;
	struct Node* next;
	Node(int data)
	{
		this->data = data;
		next = nullptr;
	}
} *head=nullptr, * front=nullptr;


/* Function to print linked list */
void print()
{
	struct Node* temp = head;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void push(int data)
{
	Node* temp = new Node(data);
	//temp->next = head;
	if (head == nullptr) {
		head = temp;
		front = temp;
	}
	else {
		front->next = temp;
		front = front->next;
	}

}

Node* pair_wise_rev(Node* head) {
	
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	Node* temp = head->next;
	head->next = temp->next;
	temp->next = head;
	head = temp;
	
	head->next->next = pair_wise_rev(head->next->next);
	return head;
}


int main() {

	/* Start with the empty list */
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);
	push(6);
	print();
	head = pair_wise_rev(head);
	print();
	return 0;

}