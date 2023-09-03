#include<iostream>
#include<vector>
#include<map>

using namespace std;


class Test {

public:
	Test(int a) { 
		x = a; 
		cout << "default ctor called" << endl;	
	}	
	Test(const Test& tst) :x(tst.x){
		cout << " copy ctor called" << endl;	
	}	
	Test(Test&& tst) noexcept :x(std::move(tst.x)) {
		cout << "Move c'tor called" << endl;
	}	
	int getX() const { return x; }
	void setX(int a) { x = a; }
private:
	int x;
};

template<typename T>
class List {

public:

	void push_back(T var) {

	}

private:
	T* data;
	unsigned int count;
};

struct variant { int x, y; };


int main() {
	vector<Test> test;
	test.push_back(10);


	List<variant> lst;

	lst.push_back({ 2,6 });


	/*

	//Test t;
	const Test t(10);
	t.getX();

	std::map<string, int> strMap = { {"First",1}, {"Second",2},{"Third",3} };
	for (auto iter = strMap.begin(); iter != strMap.end();) {
	
		
		if (iter->first == "Second") {
			iter->second = 100; // strMap.erase(iter);
		}
		//iter++;

	
	}

	
	for (auto element : strMap) {		
		if (element.first == "Second") {
			strMap.erase(element.first);
			break;
		}
	}
	

	
	for (auto &element : strMap) {
		//cout << element.first <<endl;

		if (element.first == "Second") {
			element.second = 100;
		}
	}
	

	for (auto element : strMap) {
		cout << element.second <<endl;
	}
	*/




	return 0;
}
