#include<iostream>

class Widget {

public:
	Widget(int val):data(val){}
	Widget& operator= (Widget& rhs) {
		this->data = rhs.data;     //w1.data=w2.data, once assigned data to w1 
		return *this;              //return w1 by ref..seems logical
	}

	int getdata() { return data; }
private:
	int data;
};


int main() {

	Widget w1(1000);
	Widget w2(12000);
	w1 = w2;  // similer to:: w1.operator=(w2);

	std::cout << w1.getdata();
	return 0;
}