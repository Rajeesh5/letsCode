#include<iostream>
using namespace std;


template<typename T>
void f1(T& param) {}			// param is a reference.

template<typename T>
void f2(const T& param) {}		// param is now a ref-to-const.

template<typename T>			// If param were a pointer(or a pointer to const), its
void f3(T* param) {}			// work essentially the same way.

template<typename T>
void f4(T&& param) {}			// param is now a universal reference

template<typename T>
void f5(T param) {}				// param is now passed by value


int main() {

	int x = 27;			// x is an int
	const int cx = x;	// cx is a const int
	const int& rx = x;	// rx is a reference to x as a const int

	// The deduced types for paramand T in various calls are as follows :
	
	f1(x);			// T is int,       param's type is int&
	f1(cx);			// T is const int, param's type is const int&
	f1(rx);			// T is const int, param's type is const int&

	f2(x);			// T is int, param's type is const int&
	f2(cx);			// T is int, param's type is const int&
	f2(rx);			// T is int, param's type is const int&

	const int* px = &x; // px is a ptr to x as a const int

	f3(&x);			// T is int, param's type is int*
	f3(px);			// T is const int, param's type is const int*

	f4(x);			// x is lvalue, so T is int&, param's type is also int&
	f4(cx);			// cx is lvalue, so T is const int&, param's type is also const int&
	f4(rx);			// rx is lvalue, so T is const int&, param's type is also const int&
	f4(27);			// 27 is rvalue, so T is int, param's type is therefore int&&

	f5(x);			// T's and param's types are both int
	f5(cx);			// T's and param's types are again both int
	f5(rx);			// T's and param's types are still both int

	const char* const ptr = "Fun with pointers";	// ptr is const pointer to const object		
	f5(ptr);										// pass arg of type const char * const

	const char name[] = "J. P. Briggs";				// name's type is const char[13]
	const char* ptrToName = name;					// array decays to pointer

	f5(name);										// what types are deduced for T and param?
	f1(name);										// where, param is a reference.




	return 0;
}