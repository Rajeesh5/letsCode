#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



void findPair(vector<int>& arr, int index, int sum) {


}


int main() {

	vector<int> arr = { -3,0,1,-2,-1,-2,1,2 };
	sort(arr.begin(), arr.end());

	for (int index = 0; arr[index] < 0 && index < arr.size(); index++) {
		if ( arr[index] != arr[index + 1]) {
			findPair(arr, index, -arr[index]);
		}
	}


	return 0;
	//int arr1[] = { -3,0,1,-2,-1,-2,1,2 };
	//sort(arr1, arr1+8);
}