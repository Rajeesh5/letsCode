#include "Header.h"

class List;

struct Node {
	Node(int _key) :key(_key), next(NULL) {}
private:
	int key;
	Node* next;
	friend class List;
};

class List {

public:
	List():m_phead(NULL){}
	void appendNode(Node*);
	~List() {
		while (m_phead) {
			Node* tmp = m_phead;
			m_phead = m_phead->next;
			cout << "Deleted Node:" << tmp->key << "\n";
			delete tmp;
		}
	}
	void show();
	void setKey(Node* node, int _key) { node->key = _key; }
	void creatList();
	Node* reverseList();
	const Node* getHead() { return m_phead; }

	friend void rearrangeList(List&);


private:
	Node* m_phead;
};

void List::creatList() {	
	this->appendNode(new Node(10));
	this->appendNode(new Node(20));
	this->appendNode(new Node(30));
	this->appendNode(new Node(40));
	this->appendNode(new Node(50));
	this->appendNode(new Node(60));	
}

Node* List::reverseList() {




}

void List::appendNode(Node* nd) {
	if (m_phead == NULL) {
		m_phead = nd;
	}
	else {
		Node* walker = m_phead;
		while (walker->next) {
			walker = walker->next;
		}
		walker->next = nd;
	}
}

void List::show() {
	Node* walker = m_phead;
	while (walker->next) {
		cout << walker->key << "->";
		walker = walker->next;
	}
	cout << "\n\n";
}


int main() {
	List list;
	list.creatList();
	list.show();




	return 0;
}

