#include<iostream>
#include<deque>

using namespace std;

template<typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
	return x + y;
}

auto square(float x) -> float { 
	return x * x; 
}

// But from C++14 it is possible to directly derive the return value 
// of a normal function

template<typename T, typename U>
auto add3(T x, U y) {
	return x + y;
}


template<typename Containter,typename Index>
auto authAndProcess(Containter& c, Index i) ->decltype (c[i]){
	// autheticateUser();
	return c[i];
}


template<typename Containter, typename Index>
auto authAndProcess1(Containter& c, Index i) {
	// autheticateUser();
	return c[i];
}

template<typename Containter, typename Index>
decltype(auto) authAndProcess2(Containter& c, Index i) {
	// autheticateUser();
	return c[i];
}



auto add(int x, int y) {
	return (x + y);
}

auto increment(int& p) {
	p++;
	return p;
}




int main() {
	
	/*
	// after c++11
	auto w = add2<int, double>(1, 2.1);
	if (std::is_same<decltype(w), double>::value) {
		std::cout << "w is double: ";
	}
	std::cout << w << std::endl;
	
	// after c++14
	auto q = add3<double, int>(1.1, 2);
	if (std::is_same<decltype(q), double>::value) {
		std::cout << "q is double: ";
	}
	std::cout << "q: " << q << std::endl;


	auto a = 5;
	auto b = 7;
	auto c = 9.9;
	auto d = 8.7;
	
	auto e = a * b + c * d;

	if (std::is_same<decltype(e), double>::value) {
		std::cout << "e is double " << endl;
	}


	decltype (a * b + c * d) f;

	if (std::is_same<decltype(f), double>::value) {
		std::cout << "f is double " << endl ;
	}

	*/

	
	int x = 23;
	const int cx = x;
	const int& rx = x;
	
	int&& uref = 27;						// rvalue, universal-ref
	
	auto x1 = cx;							// type of x1 = int
	decltype(auto) x2 = cx;					// type of x2 = const int

	auto x4 = rx;							// type of x4 = int
	decltype(auto) x4 = cx;					// type of x4 = const int&

	auto x5 = std::move(uref);				// type of x5 = int
	decltype(auto) x6 = std::move(uref);	// type of x4 = const int&


	//auto x2 = cx;					// type = int
	
	//
	//auto& x4 = x;       // type = int
	//auto& x5 = cx;      // type = const int
	//auto& x6 = rx;      // type = const int&



	int x = 9;
	int &y = increment(x);  //where y is refrence of x









	std::deque<int> d;
	
	//authAndProcess1( d, 5 ) = 10;    // Compilation Error!!
	authAndProcess2(d, 5) = 10;        // Fine.






	return 0;
}