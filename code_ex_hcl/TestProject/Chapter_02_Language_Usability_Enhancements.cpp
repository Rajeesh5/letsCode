#include<iostream>
#include<vector>
#include<map>
#include<initializer_list>
#include<functional>




using namespace std;

void foo(char* ch) {
	std::cout << "Inside foo char*" << std::endl;
}
void foo(int i) {
	std::cout << "Inside foo int" << std::endl;
}

// <<nullptr, nullptr_t>>
// Some compiler treat NULL as ((void*)0) and others directly as 0. Then the foo(NULL); 
// statement will call foo(int). To solve this problem, C++11 introduced the nullptr 
// keyword, which is specifically used to distinguish null pointers, 0.

void test_nullptr() {

	if (std::is_same<decltype(NULL), decltype(0)>::value) {
		std::cout << "NULL == 0" << std::endl;
	}

	if (std::is_same<decltype(NULL), decltype((void*)0)>::value) {
		std::cout << "NULL == (void *)0" << std::endl;
	}

	// Note:: The type of nullptr is nullptr_t
	if (std::is_same<decltype(NULL), std::nullptr_t>::value) {
		std::cout << "NULL == nullptr" << std::endl;
	}

	foo(NULL);
	foo(0);
	foo(nullptr);
}

constexpr int fibonacci(const int n) {
	return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

void test_auto_type() {

	//	auto x1 { 1,2,3 };      // Error, only support one element.
	auto x2 = { 1,2,3 };	    // as in C++14, x's type ≡ std::initializer_list<int>
	auto x3{ 17 };				// direct init w/1 element, x's type ≡ int
	auto x5(17);				// x's type ≡ int
	auto x4 = { 17 };           // as in C++14, x's type ≡ std::initializer_list<int>
	
	// Note :: auto x = {expr}
	// decltype(x) <> decltype(expr)
	// decltype(x) == inilializer_list<decltype(expr)>

	
	vector<int> v;
	unsigned size = v.size();	// Wrong type, correct type is: std::vector<int>::size_type
	auto sz = v.size();			// type of sz is: std::vector<int>::size_type

	// Avoid temporary object creation:

	std::map<string, int> mp;	// hold object of type: pair<const std::string,int>

	for (const pair<const string, int>& elem : mp) {}	// each interation creates temp object.
	for (auto elem : mp) {}								// no temprory object cretaed.

	std::function<int(int)> func1 = [=](int x) {return (int)(x * x + sz); };
	auto func2 = [=](int x) {return (int)(x * x + sz); };


}

void test_uniform_intialization() {
	int x1   { 10 };				// buildin ints
	struct Point { int x, y; };
	Point p2   { 10,20 };
	std::string str  { "Rajeev Sharma" };
	class Widget {
		int id1,id2;
	public:
		Widget(int x1, int y1) :id1{ x1 }, id2{ y1 } {};
		Widget(std::initializer_list<int> ini){}
	};

	Widget w{ 10,20 };			//Now call intializer list constor.
	int arr[]  { 1,2,3 };
	std::vector<int> v2   { 1,2,3 };

}

int main() {
	
	// test_nullptr();

	// About: constexpr
	// Compiler can directly optimizeand embed these expressions into the program at 
	// compile - time, it will increase the performance of the program.
	
	// constexpr int  num = fibonacci(10);    // Determine valume of num at compile time. 

	// test_auto_type();

	test_uniform_intialization();

	return 0;

}