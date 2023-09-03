#include<iostream>
#include<unordered_map>
#include<set>
#define max(a,b) (((a)>(b)) ? (a):(b))

int findLenth(const std::string& str) {
	int start = 0, end = 0, maxlen =0;
	std::unordered_map<char, int> charIndexMap;

	for (; end < str.length(); end++) {
		char rightchar = str[end];

		if (charIndexMap.find(rightchar) != charIndexMap.end()) {
			start = max(start, charIndexMap[rightchar] + 1);
			//start++;
		}
		charIndexMap[rightchar] = end;
		maxlen = max(maxlen, end - start + 1);
	}
	return maxlen;
}

int findLen(const std::string& str) {
	std::set<char> setchar;
	int start = 0;
	int maxlen = 0;
	for (int end = 0; end < str.length(); end++) {
		char rightChar = str[end];

		while (setchar.find(rightChar) != setchar.end()) {
			setchar.erase(str[start++]);
		}
		setchar.insert(rightChar);
		maxlen = max(maxlen, end - start + 1);
	}
	return maxlen;
}

int main() {

	int len =  findLen("aabccbb");
	int len1 = findLen("abcabcbb");
	return 0;
}