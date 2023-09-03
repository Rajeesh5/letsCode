#include "Header.h"



// A structure to represent a stack
class StackNode {
public:
	int data;
	StackNode* next;
};

StackNode* top = NULL;

StackNode* newNode(int data)
{
	StackNode* stackNode = new StackNode();
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

int isEmpty(StackNode* top)
{
	return !top;
}

//Both strategies work.However, a lot of programs that use a linked list use 
//a double pointer to add a new node.I know what a double pointer is.But 
//if a single pointer would be sufficient to add a new node why do a lot of 
//implementations rely on double pointers ?



//Some implementations pass a pointer to pointer parameter to allow changing 
//the head pointer directly instead of returning the new one.Thus you could write :

void push(StackNode** top, int data)
{
	StackNode* stackNode = newNode(data);
	stackNode->next = *top;
	*top = stackNode;
	cout << data << " pushed to stack\n";
}

//The implementation that doesn't take a pointer to the head pointer must return the 
//new head, and the caller is responsible for updating it itself:

StackNode* push1(StackNode* top, int data)
{
	StackNode* stackNode = newNode(data);
	stackNode->next = top;
	top = stackNode;
	cout << data << " pushed to stack\n";
	return top;
}

int pop(StackNode** top)
{
	if (isEmpty(*top))
		return INT_MIN;
	StackNode* temp = *top;
	*top = (*top)->next;
	int popped = temp->data;
	free(temp);

	return popped;
}

int peek(StackNode* top)
{
	if (isEmpty(top))
		return INT_MIN;
	return top->data;
}

// Driver code
int main()
{
	StackNode* top = NULL;

	push(&top, 10);
	push(&top, 20);
	push(&top, 30);
	top=push1(top, 40);

	cout << pop(&top) << " popped from stack\n";

	cout << "Top element is " << peek(top) << endl;

	return 0;
}




