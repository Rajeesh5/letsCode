

#include<iostream>
#include <atlstr.h>
using namespace std;

class Dog {

public:
	Dog(string name):m_name(name) {
		cout << "Dog is created: " << name << endl;		
	}
	~Dog() { cout << "dog is destroyed: " << m_name << endl; }


	void MakeRelataionShip(shared_ptr<Dog>& f) { m_pFriend = f; }
	void Bark() { cout << m_name << " Barks!!" << endl; }

private:

	// Which pointer is better choice. 
	// shared_ptr<Dog> m_pBrother;
	// Dog*            m_pBrother;
	// weak_ptr<Dog>   m_pBrother;
	string m_name;
};



int main() {
		
	

	shared_ptr<Dog> Peter= make_shared<Dog>("Peter");
	shared_ptr<Dog> Rocky = make_shared<Dog>("Rocky");

	// Rocky & Rocky both are friend's of each other.
	Peter->MakeRelataionShip(Rocky);
	Rocky->MakeRelataionShip(Peter);

	// Raw Pointer
	// With this approach, if Peter is destroyed, but Rocky continues pointing to
	// the Peter and end up with dangling pointer. That would yield undefined
	// behavior.

	// In this design, Peter and Rocky contain std::shared_ptrs to each
	// other.The resulting std::shared_ptr cycle(A points to B and B points to A) 
	// will	prevent both A and B from being destroyed. Even at the end of the block
	// still they have use count = 1 which prevent from delete and causes resource leak.




	


	return 0;

}