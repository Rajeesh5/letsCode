#include<iostream>
#include<type_traits>

using namespace std;


template<typename T>
auto print_type_info(const T& num) {

	if constexpr(is_integral<T>::value) {
		cout << "Int data-type" << endl;
		return num + 1;
	}
	else if constexpr (is_floating_point<T>::value) {
		cout << "Float data-type" << endl;
		return num + 0.1;
	}
	else {
		cout << "Unsuported data-type" << endl;
		return 0;
	}
}



int main() {

	cout << print_type_info(20) << endl;
	cout << print_type_info(36.63) << endl;

	return 0;
}