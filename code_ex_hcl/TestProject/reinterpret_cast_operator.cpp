#include "Header.h"

/*
NOTES::
reinterpret_cast, for casts between unrelated types such as pointer to int.

REMARKS::

Misuse of the reinterpret_cast operator can easily be unsafe. Unless the desired conversion is inherently low-level, 
you should use one of the other cast operators.The reinterpret_cast operator can be used for conversions such as 
char* to int*, or One_class* to Unrelated_class*, which are inherently unsafe.

The result of a reinterpret_cast cannot safely be used for anything other than being cast back to its original type.
Other uses are, at best, nonportable. The reinterpret_cast operator cannot cast away the const, volatile, 
or __unaligned attributes. The reinterpret_cast operator converts a null pointer value to the null pointer value 
of the destination type.
*/


// One practical use of reinterpret_cast is in a hash function, which maps a value to an index in such a way that 
// two distinct values rarely end up with the same index.

// Returns a hash code based on an address
unsigned short Hash(void* p) {
    unsigned int val = reinterpret_cast<unsigned int>(p);
    return (unsigned short)(val ^ (val >> 16));
}

using namespace std;
int main_2() {

    //The following example illustrates how reinterpret_cast differs from static_cast.

    const char* str = "hello";
    //int i = static_cast<int>(str);            // error C2440: 'static_cast' : cannot
                                                // convert from 'const char *' to 'int'
    int j = (int)str;                           // C-style cast. Did the programmer really intend to do this?
    int k = reinterpret_cast<int>(str);         // Programming intent is clear.
                                                // However, it is not 64-bit safe.



    // The reinterpret_cast allows the pointer to be treated as an integral type.The result is 
    // then bit - shifted and XORed with itself to produce a unique index(unique to a high degree of 
    // probability).The index is then truncated by a standard C - style cast to the return type of 
    // the function.

    int a[20];
    for (int i = 0; i < 20; i++) 
        cout << Hash(a + i) << endl;


    
    
    

    return 0;
}

