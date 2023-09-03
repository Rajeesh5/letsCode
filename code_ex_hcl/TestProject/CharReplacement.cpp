#include<iostream>
#include<unordered_map>
#define max(a,b) (((a)>(b)) ? (a):(b))


int findLen(const std::string& str, int k) {
	int start = 0, end = 0, maxlen = 0, maxRepeatCharCnt = 0;
	std::unordered_map<char, int> charfreqency;

	for (; end < str.length(); end++) {
		char rightChar = str[end];
		charfreqency[rightChar]++;
		maxRepeatCharCnt = max(maxRepeatCharCnt, charfreqency[rightChar]);

		// Decrement the windows, if (size_of_win - count_of_most_freq_char > k)
		if (/*size of windows*/ (end- start + 1) - maxRepeatCharCnt > k) {
			char leftChar = charfreqency[start++];
			charfreqency[leftChar]--;
		}
		maxlen = max(maxlen,/*size of windows*/ (end - start + 1));
	}
	return maxlen;
}

int main() {
	int len = findLen("ABABBA", 2);
}