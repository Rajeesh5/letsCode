#include "Header.h"
#include <Windows.h>
#include <atlstr.h>




void foo(void* vptr) {
	cout << static_cast<long>(reinterpret_cast<intptr_t>(vptr)) << endl;
	
}
void foo1(void* vptr) {
	cout << *(reinterpret_cast<long*>(vptr)) << endl;

}
void display(UINT_PTR id) {
	
	//CString tmp((LPCTSTR)id);
	//CString tmp;
	//tmp.Format(_T("%s\n"), id);	
	//cout << tmp;
}

int main_22() {

	/*
	CString str = CString((LPCTSTR)1611);
	LPCTSTR str1 = "Rajeev";
	cout << sizeof(str) << sizeof(str1) << endl;
	long lg = 10;
	foo((PVOID)static_cast<intptr_t>(lg));
	//foo1(&lg) ;
	*/

	char str[]=("Rajeev Sharma");
	display((UINT_PTR)str);


	CString str1 = _T("Some Data");
	str1.Format(_T("%s%d"), str, 123);

	//getchar();

	return 0;
}

