#include "Header.h"
#include <Windows.h>
int main_x() {

	int i = 100;
	LPVOID lpReserved = &i;												// typedef void* LPVOID in windef.h    


	int     x = *((int*)lpReserved);                                     // Old C style cast
	long    y = *(reinterpret_cast<long*>(lpReserved));                  // C++ style cast & even more readable.
	INT_PTR z = *(reinterpret_cast<INT_PTR*>(lpReserved));               // Safe to cast in INT_PTR

	int p = PtrToInt(lpReserved);
	cout << p << endl;


	//ptr = (void*)x;


	return 0;
}