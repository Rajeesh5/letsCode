#include "Header.h"
#include <vector>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <cstring>
#include <atlstr.h>


//std::basic_string<wchar_t> is equivalent to wstring
typedef std::basic_string<wchar_t> CQString;  
typedef std::vector<CQString> CQStringArray;

static LPCTSTR PdSqlKeywords[] = {
_T("absolute"),
_T("access"),
_T("account"),
_T("acquire"),
_T("action"),
_T("activate"),
_T("actor")
 /*etc*/
};


void ShowList(vector<LPCTSTR>& lst) {

/*
	int size = lst.size();

	LPCTSTR item = _T("");
	for (int i = 0; i < size; i++) {
		item = lst.at(i);
		cout << item << endl;
	}

	CString str;
	*/

	/*
	vector<LPCTSTR>::iterator iter = lst.begin();

	for (; iter != lst.end(); iter++) {
		cout << *iter << endl;
	}
	*/

	/*for(LPCTSTR &var: lst)
	{
		cout << var<<endl;
	}*/
}

//typedef std::vector<LPCTSTR> StrArray;
void PdGetSqlKeywordList(CQStringArray& list)
{
	const LONG 	size = sizeof(PdSqlKeywords) / sizeof(PdSqlKeywords[0]);
	for (LONG i = 0; (i < size); i++) {
		//How to make this conversion possible??
		//LPCTSTR to CQString(wstring)..  
		
		//CQString to LPCTSRT  -- Done

		//CQString str = L"Mail";
		//LPCTSTR str2 = str;


		//CQString str = PdSqlKeywords[i];	
		//list.push_back(PdSqlKeywords[i]);
	}
}


int main() {


	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);

	CString test = _T("缺陷经历时间");

	cout << test << endl;
	//sprintf(test)


	/*
	vector<LPCTSTR> strList;
	const LONG 	size = sizeof(PdSqlKeywords) / sizeof(PdSqlKeywords[0]);
	for (LONG i = 0; (i < size); i++)
		strList.push_back(PdSqlKeywords[i]);

	ShowList(strList);

	*/

	return 0;
}









/*
typedef std::vector<LPCTSTR> StrArray;
void PdGetSqlKeywordList(StrArray& list)
{
	const LONG 	size = sizeof(PdSqlKeywords) / sizeof(PdSqlKeywords[0]);
	for (LONG i = 0; (i < size); i++) {
		list.push_back(PdSqlKeywords[i]);
	}
}
	StrArray list;
	list.reserve(100);
	PdGetSqlKeywordList(list);
*/



