#include<iostream>
#include<unordered_map>
#include<string>


using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

int findMaxKthDistinctStr(string& str, int k) {

	unordered_map<char, int> charfreq;
	int maxLen = 0;
	int start = 0;
	for(int i = 0; i < str.length(); i++) {
		char ch = str[i];
		charfreq[ch]++;

		while (charfreq.size() > k)
		{
			char ch = str[start];
			charfreq[ch]--;
			if (charfreq[ch] == 0) {
				charfreq.erase(ch);
			}
			start++;

		}

		maxLen = max(maxLen, i - start+1 );
	}




	for (auto& iter : charfreq) {
		cout << iter.first << "->" << iter.second << endl;
	}

	return maxLen;

}

int main_sw_1() {

	string str = "araaccir";
	cout << findMaxKthDistinctStr(str, 3);

	return 0;
}
