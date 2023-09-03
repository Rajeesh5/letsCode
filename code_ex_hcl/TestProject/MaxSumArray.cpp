#include<iostream>
#include<vector>
#include<limits>




using namespace std;

struct Window {
	int start;
	int end;
	Window() :start(0), end(0) {}
};


int findsubarray(const int k, const std::vector<int> arr) {
	Window w;
	int maxsum=0, sum =0, start = 0;

	for (int index = 0, i = 0; index < arr.size(); index++) {
		sum += arr[index];
		if (index >= k - 1) {              
			if (maxsum < sum) {
				maxsum = sum;
				w.start = index - k +1 ;   // windows start index.   
				w.end = index;             // windows end index.  
			}
			sum = sum - arr[start++];      // increment start window index.
		}
	}
	return maxsum;
}


int findLongSeq(const std::vector<char> arr) {
	int max_cnt = 0;
	int count = 0;
	char max_char = '\0';
	char prev_char = '\0';
	for (auto curr_char : arr) {
		if (curr_char == prev_char) 
			count++;		
		else count = 1;

		if (count > max_cnt) {
			max_cnt = count;
			max_char = curr_char;
		}
		prev_char = curr_char;
	}
	return max_cnt;   // with max_char;
}



int main() {
	int s1 = findsubarray(3, std::vector<int>{1, 2, 5, 7, 3, 9});
	int s2 = findsubarray(3, std::vector<int>{2, 8, 5, 1, 3, 2});
	return 0;
}