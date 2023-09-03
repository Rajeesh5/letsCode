#include<iostream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <cstring>
#include <atlstr.h>

using namespace std;




void PrintName(int id1, LPARAM id2) {
	
	cout <<" INT id = "<< id1 << endl;
	LPARAM idd = (LPARAM)id1;    
	cout <<" converted int to lpram :: LPARM name = " << idd <<endl;
	cout<< " LPARAM id = "<< id2 << endl;

	//LPCTSTR pName1 = (LPCTSTR)id1;
	//LPCTSTR pName2 = (LPCTSTR)id2;


	//cout << (LPCTSTR) * ((CString*)id1) << endl;
	//cout << (LPCTSTR) * ((CString*)id2) << endl;

	//cout << (LPCTSTR) * ((CString*)name);	
	//LPCTSTR pName = (LPCTSTR)name;	
	//CString *str = (CString*)pName;
	//LPCTSTR pName = (LPCTSTR)*str;

}

int main() {

	std::ios oldState(nullptr);
	oldState.copyfmt(std::cout);
	std::cout << std::hex;

	

	CString name = _T("Rajeev Sharma");
	   	 
	PrintName((LPARAM)&name , (LPARAM)&name);
	std::cout.copyfmt(oldState);
	return 0;

}