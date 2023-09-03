#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


using namespace std;

vector<char> collepse(const string &test) {

	int i = 0;
	vector<char> result;
	result.push_back(test[i++]);

	//ABCCBCBA->ABBCBA->ACBA

	while (i < test.length()) {
		vector<char>::iterator it = result.end() - 1;
		//char ch = result.at(result.size() - 1);
		if (*it == test[i]) {
			result.erase(it, result.end());
		}
		else {
			result.push_back(test[i]);
		}	
		i++;
	}

	return result;
}

int main() {

	string test = "ABCCBCBA"; 

	vector<char> str = collepse(test);

	
	return 0;
}
