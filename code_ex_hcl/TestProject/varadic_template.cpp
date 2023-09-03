#include<iostream>
#include<vector>
#include<map>


// Want to generate 0 template parameters:
template<typename... Ts> 
class Magic {};

 // Define at least  one template parameter:
template<typename Require, typename... Args> 
class Magic_ {};


// c style suppoted variable argument method, like printf:
// template<typename... Args> void printf(const std::string& str, Args... args);


// count number of parameter passed:

template<typename... Ts>
void magic(Ts... args) {
	std::cout << sizeof...(args) << std::endl;
}

// Recursive-approch to unpack the varibale argument.

template<typename U>
void print_args(U value) {		// Base-case, with only 1-args
	std::cout << value << std::endl;
}

template<typename T, typename... Ts>
void print_args(T value, Ts... args) {
	std::cout << value << std::endl;
	print_args(args...);		// Recursive call.
}


// or, we can combine, base-case in same method;

template<typename T0, typename... T>
void print_args_unified(T0 t0, T... t) {
	std::cout << t0 << std::endl;
	if constexpr (sizeof...(t) > 0) print_args_unified(t...);
}


// Initialize list expansion

template<typename T, typename... Ts>
auto print_args_list(T value, Ts... args) {
	std::cout << value << std::endl;
	
	(void)std::initializer_list<T> {
		( [&args] {
			std::cout << args << std::endl;
		}(), value)...};
}


int main() {

	// The template class Magic object can accept an unrestricted number of 
	// typename as a formal parameter of the template, such as the following definition :
	Magic<int,
		std::vector<int>,
		std::map<std::string,
		std::vector<int>>> darkMagic;

	Magic<> magic1;			// No argument 
	Magic_<int> magic2;		// at-least one argument required.

	// We can pass any number of arguments to the magic function :
	magic();				// 0-argument
	magic(1);				// 1-argument
	magic(1, "x");			// 2-argument
	

	print_args("Hi", 1, 1.09, 'x');

	print_args_unified("Hi", 1, 1.09, 'x');



	return 0;
}