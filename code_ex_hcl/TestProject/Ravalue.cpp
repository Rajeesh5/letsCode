#include<iostream>
#include<vector>
using namespace std;

/*


//An rvalue reference is declared with&&
//Binds only to(unnamed) temporary objects
int fn();					// Note: return val is rvalue
int main()
{
	int i = 10, & ri = i;	// ri is ordinary lvalue ref
	int&& rri = 10;			// OK, rvalue ref to temp
	int&& rri2 = i;			// ERROR, attempt to bind
							// lvalue to rvalue ref
	int&& rri3 = i + 10;	// Fine, i + 10 is a temp
	int& ri2 = fn();		// ERROR, attempt to bind
							// rvalue to lvalue ref
	const int& ri3 = fn();	// OK, lvalue ref-to-const
	int&& rri4 = fn();		// Fine, ret. val is a temp
}

*/

class Widget {
public:
	Widget() { cout << "Widget default created" << endl; }
	Widget(const Widget& w) { cout << "Widget copy constucted" << endl; }
	~Widget() { cout << "Widget distructed" << endl; }
};


vector<Widget> foo() {
	vector<Widget> tmp(10);
	//return tmp;
	return static_cast<std::vector<Widget>&&>(tmp);
}
void reference(std::string& str) {
	std::cout << "lvalue" << std::endl;
}
void reference(std::string&& str) {
	std::cout << "rvalue" << std::endl;
}
void increase(int& v) {
	v++;
}


/*
class Blob {
public:
	// Blob’s move ops must do the “stealing”:
	Blob(Blob&& rhs) {					// move ctor 
		raw_ptr = rhs.raw_ptr;			// “steal” pointer 
		rhs.raw_ptr = nullptr;			// clear source 
	}
	Blob& operator=(Blob && rhs) {		// move assign. Op 
		if (this != &rhs) { 
			delete [] raw_ptr; 
			raw_ptr = rhs.raw_ptr;		// “steal” pointer 
			rhs.raw_ptr = nullptr;		// clear source 
		}
		return *this;
	}
private:
	char* raw_ptr;
};


// "Big" Class with Move Operations. 
// So there are now six canonical functions per class 
// (used to be four) that class authors may define
class Big {
public:
	Big();							// 1. default ctor
	~Big();							// 2. destructor
	Big(int x);						// (non-canonical)
	Big(const Big&);				// 3. copy ctor
	Big& operator=(const Big&);		// 4. copy assign.
									// 5. move ctor
	Big(Big&& rhs) :b(std::move(rhs.b)), x(rhs.x) {}
									// 6. move assign.	
	Big& operator=(Big&& rhs) {
		b = move(rhs.b);			// Note we NEED the moves, because 
		x = rhs.x;					// rhs itself is an lvalue! (even 
		return *this;				// though it has type rvalue ref)
	}

	friend Big operator + (const Big&, const Big&);
	
private:
	Blob b;							// e.g. some resource-managing type
	double x;						// other data…
};

Big makeBig() { return Big(); }
Big munge(const Big&);
Big operator + (const Big&, const Big&) {

}
*/




int main() {
	
	const vector<Widget> &vw = std::move(foo());




/*
	auto vw = std::move(foo());

	cout << typeid(vw).name() << endl;
	
	std::string lv1 = "string,";			// lv1 is a lvalue
	//std::string&& r1 = lv1;				// illegal, rvalue ref cannot be bound to lvalue
	std::string&& rv1 = std::move(lv1);		// legal, std::move can convert lvalue to rvalue ref
	std::cout << rv1 << std::endl;			// string,
	
	
	const std::string& lv2 = lv1 + lv1;		// legal, const lvalue reference can
											// extend temp variable's lifecycle
	//lv2 += "Test";						   // illegal, const ref can't be modified 
	
	std::cout << lv2 << std::endl;			// string,string,
	
	std::string&& rv2 = lv1 + lv2;			// legal, rvalue ref extend lifecycle
	rv2 += "string";						// legal, non-const reference can be modified
	std::cout << rv2 << std::endl;			// string,string,string,string
	reference(rv2);							// output: lvalue
	
	*/

//int &a = std::move(1);					// illegal, non-const lvalue reference cannot reference rvalue
	//const int& b = std::move(1);				// legal, const lvalue reference can
	//double s = 1;
	//increase(s);

/*
	

	Big x, y;			// Note: below, “created” really
	Big a;				// means “not just moved”
	a = makeBig();		// 1 Big created *
	Big b(x + y);		// 1 Big created *
	a = x + y;			// 1 Big created *
	a = munge(x + y);	// 2 Bigs created *
	std::swap(x, y);	// 0 Bigs created!

	// Note::  *: Return value’s contents moved to destination obj




	auto&& x = 3.1415;		// x is an rvalue 
	double pi = 3.14; 
	auto &&y = pi;			// y is an lvalue
	
	template<typename T>	// Here, val can be 
	void f(T &&val);		// lvalue OR rvalue!
							// functions instantiated:
	f(3.14);				// f(double &&);
	f(x);					// f(double &&); 
	f(pi);					// f(double &);

	*/





	
	return 0;
}


