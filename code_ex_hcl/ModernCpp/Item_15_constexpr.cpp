#include<iostream>
#include<type_traits>
#include<string>

using namespace std;

template<typename T>
auto print_len(const T& val)
{
	if constexpr (is_integral<T>::value) {
		return val;
	}
	else{
		return val.length();
	}
}




int main() {

	int n{ 10 };
	string s{ "Rajeev" };

	int x;

	std::cin >> x;

	constexpr int y = x;

	print_len(n);
	print_len(s);

	return 0;
}