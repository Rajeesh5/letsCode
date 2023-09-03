#include<iostream>
#include<vector>



using namespace std;

int remove_duplicate(vector<int>& arr) {

	int size = arr.size();

	int start = 0;
	int end = start + 1;
	while (end < size) {

		if (arr[start] == arr[end]) {
			end++;

		}
		else {
			start++;
			swap(arr[start], arr[end]);
			end++;			
		}

	}

	return start+1;
}


int main() {

	vector<int> arr = { 2,3,3,3,6,9,9,10,10,15,17,17,17 };

	int pos = remove_duplicate(arr);

	vector<int>::iterator iter = arr.begin() + pos;

	arr.erase(iter, arr.end());

	for (auto ele : arr) {
		cout << ele << " ";
	}



	return 0;
}