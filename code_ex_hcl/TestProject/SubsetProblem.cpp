#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;


template<class T>
class PetternSubset {
public:
	static vector<vector<T>> findsubsets(const vector<T>& nums) {
		vector<vector<T>> subsets;
		subsets.push_back(vector<T>());
		for (auto elem : nums) {
			int n = subsets.size();

			for (int i = 0; i < n; i++) {
				vector<T> set(subsets[i]);
				set.push_back(elem);
				subsets.push_back(set);
			}
		}
		return subsets;
	}
	static void powerSetRecursive(string str, int index = 0, string curr = "")
	{
		int n = str.length();

		// base case
		if (index == n) {
			cout << curr << endl;
			return;
		}

		// Two cases for every character
		//		(i) We consider the character as part of current subset
		//		(ii) We do not consider current character as part of current subset
		powerSetRecursive(str, index + 1, curr + str[index]);
		powerSetRecursive(str, index + 1, curr);
	}
	static vector<vector<T>> findSubsetWithDups(vector<T>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<T>> subsets;
		subsets.push_back(vector<T>());
		int startIndex = 0, endIndex = 0;

		for (int i = 0; i < nums.size(); i++) {
			startIndex = 0;
			
			if (i > 0 && nums[i] == nums[i - 1]) {
				// Menas duplicate, so need to copy the elememt 
				// from end of the subset, not from the begning.
				startIndex = endIndex + 1;
			}
			endIndex = subsets.size() + 1;

			for (int j = startIndex; j <= endIndex; j++) {
				vector<T> set(subsets[j]);
				set.push_back(nums[i]);
				subsets.push_back(set);
			}
		}
		return subsets;
	}
	static void printSubset(vector<vector<T>> &result) {

		cout << "Subsets are::" << endl;
		for (auto collection : result) {
			cout << "[";
			for (auto item : collection) {
				cout << item << " ";
			}
			cout << "]" << endl;
		}
		cout << "\n------------------------------\n";
	}

	static int countSetPerfectSum(const vector<int>& arr, int totalSum, int index) {
		if (totalSum == 0) {
			return 1;
		}
		else if (totalSum < 0) return 0;	// set not found.
		else if (index == 0) return 0;		// Reached at lower bound.
		else if (totalSum < arr[index]) {	// exclude this element
			return countSetPerfectSum(arr, totalSum, index - 1);
		}
		else {
			countSetPerfectSum(arr, totalSum - arr[index], index - 1) +		// include index element 
				countSetPerfectSum(arr, totalSum, index - 1);               // exclude index element
		}
	}
};

int main() {

	//vector<vector<char>> subset = PetternSubset<char>::findsubsets(vector<char>{'A','B', 'C'});
	//PetternSubset<int>::powerSetRecursive("ABC");

	//vector<char> dups = { 'A', 'B', 'B','C' };
	//vector<vector<char>> subset = PetternSubset<char>::findSubsetWithDups(dups);
	//PetternSubset<char>::printSubset(subset);

	cout<< PetternSubset<int>::countSetPerfectSum(vector<int>{2, 4, 6, 10}, 16 /*sum*/, 3/*arrLen*/);

	return 0;
}
