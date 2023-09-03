#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>


using namespace std;


int addxy(int first, int second) {
	return first + second;
}



template<typename Containter, typename Function>
void apply(Containter& collection, const Function &func) {
	for (auto &element : collection) {
		func(element);
	}
}

// apply1 is same to apply
template<typename Containter, typename T>
void apply1(Containter& collection, function<void(T&)> const func) {
	for (auto& element : collection) {
		func(element);
	}
}


void lambda_value_capture() {
	int value = 1;

	auto copy_value = [value] {
		return value;
	};

	value = 100;
	auto stored_value = copy_value();

	std::cout << "stored_value = " << stored_value << std::endl;
	// At this moment, stored_value == 1, and value == 100.
	// Because copy_value has copied when its was created.
}


int main() {

	/*
	std::vector<int> v(10, 0);
	for_each(v.begin(), v.end(), [](int val) { cout << val << " "; });

	// name-less method called with string parameter “Hi” 
	[](auto x) {cout << x << endl; } ("Hi");

	//Lambda with new return systex.
	cout << [](auto val)-> auto { return val * val; } (10.3) << endl;


	//Storing lambda

	auto square = [](auto val)-> auto { return val * val; };
	cout << square(12.36) << endl;

	std::function<int(int, int)> add = [](int x, int y) {return (x + y); };
	cout << add(10, 20) << endl;

	using namespace std::placeholders;	 //placeholder for _1,_2 etc 

	auto mult = std::bind([](int x, int y) -> int {return (x * y); }, _1, _2);
	// Returning of above bind method: function<int(int,int)> 

	cout << mult(12,36) << endl;

	*/


	vector<int> v1(10, 2);		// Size = 10, intial value = 2;
	apply(v1, [&](int &x){ x = +2; });






	return 0;
}

