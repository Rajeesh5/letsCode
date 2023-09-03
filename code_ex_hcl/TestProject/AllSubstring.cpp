#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

void subString1(string s, int n)
{
    // Pick starting point in outer loop
    // and lengths of different strings for
    // a given starting point
    for (int i = 0; i < n; i++)
        for (int len = 1; len <= n - i; len++)
            cout << s.substr(i, len) << endl;
}


void subString(string str, vector<string> &substrs)
{
    // Pick starting point
    size_t n = str.length();
    for (int len = 1; len <= n; len++)
    {
        // Pick ending point
        for (int i = 0; i <= n - len; i++)
        {
            //  Print characters from current
            // starting point to current ending
            // point. 
            int j = i + len;            
            
            //bounding tmp object.
            substrs.push_back(static_cast<string&&>
                (string(str.begin() + i, str.begin() + j)));
            
            // or, substrs.push_back(std::move(string(str.begin() + i, str.begin() + j)));
        }
    }
}

int main() {

    vector<string> substrings;
    subString("geeksforgeeks",substrings);



    map<string, int> stringCntMap;
    int maxCnt = -1;
    string maxcntStr;
    for (auto ele : substrings) {
        stringCntMap[ele]++;


        if (maxCnt < stringCntMap[ele]) {
            maxCnt = stringCntMap[ele];
            maxcntStr = ele;
        }
    }

    for (auto &ele : stringCntMap) {
        cout << ele.first <<" ->" <<ele.second << endl;
    }


    return 0;
}