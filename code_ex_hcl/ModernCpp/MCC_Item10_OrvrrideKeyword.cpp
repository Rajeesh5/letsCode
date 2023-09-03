#include<iostream>

using namespace std;

class Widget {
public:

	void doWork()&;			// this version of doWork applies
							// only when *this is an lvalue
	void doWork()&&;		// this version of doWork applies
};							// only when *this is an rvalue

Widget makeWidget();		// factory function (returns rvalue)


class Base {
public:
	virtual void mf1() const;
	virtual void mf2(int x);
	virtual void mf3()&;
	void mf4() const;
};
class Derived : public Base {
public:
	virtual void mf1();				 // mf1 is declared const in Base, but not in Derived.
	virtual void mf2(unsigned int x);// mf2 takes an int in Base, but an unsigned int in Derived.
	virtual void mf3()&&;            // mf3 is lvalue - qualified in Base, but rvalue - qualified in Derived.
	void mf4() const;                // mf4 isn’t declared virtual in Base.
};



class Derived : public Base {
public:
	virtual void mf1()override;
	virtual void mf2(unsigned int x) override;
	virtual void mf3() && override;
	virtual void mf4() const override;
};

int main() {
	Widget w;				// normal object (an lvalue)
	w.doWork();				// calls Widget::doWork for lvalues
							// (i.e., Widget::doWork &)
	makeWidget().doWork();	// calls Widget::doWork for rvalues
							// (i.e., Widget::doWork &&)
	return 0;
}




