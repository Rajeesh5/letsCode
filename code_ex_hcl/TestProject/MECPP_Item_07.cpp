#include<iostream>
#include<vector>

using namespace std;

class Widget {
public:
	Widget(int i, bool b) :x(i), y(b) {};
	Widget(int i, double d) :x(i), y(d) {};
	Widget(std::initializer_list<long double> il):x(0),y(0) {
		int i = 0;
		for (auto item : il) {
			if (i == 0) {
				x = item;
			}
			if (i == 1) {
				y = item;
			}
			i++;
		}	
	}
private:
	int x;
	int y;
};
int main() {
	vector<int> v1 = { 1,2,3,4,5 };
	vector<int> v2   { 1,2,3,4,5 };
	vector<int> v3(10, 0);

	for (auto ele : v3) {
		cout << ele << " ";
	}

	Widget w1{ 10,23 };

	return 0;
}
