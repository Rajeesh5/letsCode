#include<iostream>
#include<atlstr.h>

using namespace std;


int main() {
	/*
	CString str = "    \".sysxatab";

	str.TrimLeft();
	str.Remove('.');
	str.Remove('\"');

	cout << str;

	*/

	CString tablename = "\"wh01rs_1\".actiondef";
	CString owner = "wh01rs_1";

	tablename.Remove('\"');
	CString table = tablename.Right(tablename.GetLength() - owner.GetLength() - 1);


		std::cout << table;



	getchar();

}