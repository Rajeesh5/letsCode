#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;


class Solution {
public:
    static bool isAnagram(string s, string t) {
        auto len = s.length();
        int index = 0;
        bool ans = true;

        map<char, int> frequency;

        if (s.length() != t.length()) {
            return false;
        }
        while (index < len) {
            frequency[s[index]]++;
            index++;
        }
        index = 0;

        while (index < len) {
            if (frequency.find(t[index]) != frequency.end())
            {
                frequency[t[index]]--;
            }
            else {
                ans = false;
                break;
            }
            index++;
        }
        if (ans) {
            for (auto& element : frequency) {
                if (element.second != 0) {
                    ans = false;
                    break;
                }
            }
        }
        return ans;
    }

    static vector<vector<string>> groupAnagrams(const vector<string>& strs) {

        vector<vector<string>> result;
        vector<string> row;

        for (int i = 0; i < strs.size(); i++) {
            row.push_back(strs[i]);

            for (int j = i + 1; j < strs.size(); j++) {
                if (isAnagram(strs[i], strs[j])) {
                    row.push_back(strs[j]);
                }
            }

            result.push_back(row);
            row.clear();
        }

        return result;
    }
};


int main() {

    //Solution::isAnagram("aacc", "ccac");
    //vector<vector<string>> result = Solution::groupAnagrams({ "eat", "tea", "tan", "ate", "nat", "bat" });

    vector<int> v{ 1,2,3,4,5,6,7,8,9 };
    for_each(v.begin(), v.end(), [](int& i) { i = i * 10; return i; });

    for (auto ele : v) {
        cout << ele << " ";
    }


    return 0;
}