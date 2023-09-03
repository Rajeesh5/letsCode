#include<iostream>
#include<vector>

class Widget{};

std::vector<Widget> createWidgetV() {
	std::vector<Widget> vw;

	vw.push_back(Widget());
	vw.push_back(Widget());
	vw.push_back(Widget());

	// ...
	return vw;
}

template<typename T>									
void f(const T& param) {				
	
	using std::cout;

	cout << "T = " << typeid(T).name() << '\n';			// show T
	cout << "param = " << typeid(param).name() << '\n'; // show param's type

} 







int main() {



	const int theAnswer = 42;
	
	// An IDE editor would likely show that x’s deduced type was 
	// intand y’s was const	int*.
	auto x = theAnswer;
	auto y = &theAnswer;

	// But, If that compiler can’t make enough sense of code to parse it and
	// perform type deduction, it can’t show what types it deduced.


	// Determing type at runtime.
	std::cout << typeid(x).name() << '\n';				// display types for
	std::cout << typeid(y).name() << '\n';				// x and y
				

	const auto vw = createWidgetV();					// factory function

	if (!vw.empty()) {
		f(&vw[0]);										// template function f to be called
	}

	return 0;
}