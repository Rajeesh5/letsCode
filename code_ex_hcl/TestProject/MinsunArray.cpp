#include<iostream>
#include<vector>
#include<limits>



using namespace std;

struct Window {
	int start;
	int end;
	Window():start(0),end(0){}
};

int min(int first, int second) {
	return first < second ? first : second;
}

int findMinWindowSize(int sum, const vector<int>& arr) {
	Window window;
	int minWindowsize = INT_MAX;
	int totalSum = 0;

	for (int index = 0; index < arr.size(); index++) {
		totalSum += arr[index];
		while (totalSum >= sum) {
			minWindowsize = min(minWindowsize, (window.end - window.start + 1));
			totalSum = totalSum - arr[window.start];
			window.start++;				
		}
		window.end++;
	}
	return minWindowsize;
}

int main() {
	cout << findMinWindowSize(7, vector<int>{2, 1, 5, 2, 3, 2}) << endl;
	cout << findMinWindowSize(8, vector<int>{3, 4, 1, 1, 6}) << endl;
	cout << findMinWindowSize(7, vector<int>{2, 1, 5, 2, 8}) << endl;
}