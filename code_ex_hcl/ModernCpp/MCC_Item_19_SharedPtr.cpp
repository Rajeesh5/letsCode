#include<iostream>

using namespace std;



class Widget {
public:
	Widget(int id):m_id(id){}
	int getID() { return m_id; }
	void setID(int id) { m_id = id; }
private:
	int m_id;
};


int main() {

	shared_ptr<Widget> sp1 = make_shared<Widget>(new Widget(100));
	shared_ptr<Widget> sp2 = std::move(sp1);

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
	return 0;

}