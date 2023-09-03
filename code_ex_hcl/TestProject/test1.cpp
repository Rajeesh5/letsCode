#include<iostream>
#include<vector>
#include<atlstr.h>

using namespace std;


BOOL AdIsHex(CString& string)
{
    BOOL    result = TRUE;
    size_t  length = string.GetLength();
    string.MakeUpper();

    // Iterate over string and check if the character is invalid
    for (int i = 0; i < length; i++)
    {
        char ch = string[i];

        if ((ch < '0' || ch > '9') &&
            (ch < 'A' || ch > 'F'))
        {
            result = false;
            break;
        }
    }
    return result;
}

void duplicateCount(vector<string>& names) {
    int rank = 1;
    int index = 0;
    int len = names.size();

    while(index < len) {
        int  nxtIndex  = index + 1;
        while ( (nxtIndex < len ) && names.at(index) == names.at(nxtIndex)) {
            cout << names.at(index) << "," << rank << endl;
            nxtIndex++;
            rank++;
        }
         cout << names.at(index) << "," << rank << endl;
        index = nxtIndex;
        rank = 1;
    }
    
}

void duplicateSite(vector<std::pair<string, string>>& names_site,vector<string> &names) {

    int index = 0;
    int len = names.size();
    bool duplicate = false;
    std::pair<string, string> user_site;
    while (index < len) {
        int  nxtIndex = index + 1;        
        while ((nxtIndex < len) && names.at(index) == names.at(nxtIndex)) {
            user_site = names_site.at(index);
            names.at(index).append(_T(".") + user_site.second);
            nxtIndex++;
            index++;
            duplicate = true;
        }
        if (duplicate) {
            user_site = names_site.at(index);
            names.at(index).append(_T(".") + user_site.second);
        }
        index = nxtIndex;    
        duplicate = false;
    }



}

int main() {

    /*

    CString str = _T("12345abc23");

    if (AdIsHex(str)) {
        cout << "HEX" << endl;

    }
    else {
        cout << "Not Hex" << endl;
    }

    */

    vector<string> names = {
        "Dave",
        "Haana",
        "Joy",
        "Joy",
        "Rajeev",
        "Sunil",
        "Sunil",
        "Sunil",
        "Sunil",
        "Rohan",
        "Rohan"};

    vector<std::pair<string, string>> names_site = {
    {"Dave","SiteA"},
    {"Haana","SiteA"},
    {"Joy","SiteA"},
    {"Joy","SiteB"},
    {"Rajeev","SiteA"},
    {"Sunil","SiteA"},
    {"Sunil","SiteB"},
    {"Sunil","SiteC"},
    {"Sunil","SiteD"},
    {"Rohan","SiteA"},
    {"Rohan","SiteB"}
    };

  
    //duplicateCount(names);

    duplicateSite(names_site, names);


    return 0;
}