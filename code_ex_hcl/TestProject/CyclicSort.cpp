#include<iostream>
#include<vector>

using namespace std;


class CyclicSort {
public:
	static void sort(std::vector<int>& arr) {
		int index = 0;		

		while (index < arr.size()) {
			int j = arr[index] - 1;       // index must be 0 indexed
			if (arr[index] != arr[j]) {   // if(arr[index]! = its index value)
				swap(arr[index], arr[j]);
			}
			else {
				index++;
			}
		}
	}

	static int findMissingNumber(std::vector<int>& arr) {
		int index = 0;
		while (index < arr.size()) {
			// Ignore the number whose value is more then array size.
			if ( arr[index] < arr.size() && arr[index] != arr[arr[index]]) {  
				swap(arr[index], arr[arr[index]]);
			}
			else {
				index++;
			}
		}

		for(int i = 0; i < arr.size(); i++) {
			if (arr[i] != i)
				return i;
		}

		return arr.size();
	}

	static int findDups(std::vector<int>& arr) {
		int index = 0;
		while (index < arr.size()) {
			if (arr[index] != index + 1 &&  arr[index] != arr[arr[index]-1]) {
				swap(arr[index], arr[arr[index] - 1]);
			}
			else {
				return arr[index];
			}
			
		}
	}
private:
	static void swap(int& x1, int& x2) {
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
};

int main() {

	/*
	vector<int> arr = { 2,6,1,5,3,4 };
	CyclicSort::sort(arr);

	for (auto elem : arr) {
		std::cout << elem << " ";
	}
	*/
	vector<int> arr1 = { 4,0,3,1 };
	cout << CyclicSort::findMissingNumber(arr1);



}