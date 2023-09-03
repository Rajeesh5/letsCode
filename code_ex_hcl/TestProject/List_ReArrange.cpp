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
};

struct LinkedList {
	Node* head;
	Node* front;

	LinkedList()
	{
		head = nullptr;
	}

	/* Function to reverse the linked list */
	Node* reverse(Node* node)
	{
		if (node == nullptr)
			return nullptr;
		if (node->next == nullptr) {
			head = node;
			return node;
		}
		Node* temp = reverse(node->next);
		temp->next = node;
		node->next = nullptr;
		return node;
	}

	/* Function to print linked list */
	void print()
	{
		struct Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
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

	void rearrangeList();

};


// Rearrange the List. 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> N
// your method should return 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> N.
void LinkedList::rearrangeList() {

	if (head == nullptr && head->next == nullptr) {
		return;
	}

	Node* slow = head;
	Node* fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	Node* firstHalf = head;
	bool isOdd = false;
	if (fast) {
		// menas, list is odd;
		isOdd = true;
		reverse(slow->next);
	}
	else {
		//means list is even;
		reverse(slow);
	}
			
	// Now Head is pointing to next half node in rev-order.
	Node* secondHalf = head;

	head = nullptr;		//re-store the head & front 
	front = nullptr;

	while (firstHalf && secondHalf) {
		push(firstHalf->data);
		push(secondHalf->data);
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	// Only applicable for odd list
	if (isOdd) {
		push(firstHalf->data);
	}



}


/* Driver program to test above function*/
int main()
{
	/* Start with the empty list */
	LinkedList ll;
	ll.push(1);
	ll.push(2);
	ll.push(3);
	ll.push(4);
	ll.push(5);
	ll.push(6);

	ll.rearrangeList();
	ll.print();



	return 0;
}
