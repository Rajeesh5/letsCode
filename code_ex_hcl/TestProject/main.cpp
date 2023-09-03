#include "Header.h"
#include <Windows.h>

#pragma warning( push )
#pragma warning( disable : 4838)


static const LONG testValues[][2] = {
    {0,          0},
    {1,          0x01000000},
    {-1,         -1},               // -1 is 0xFFFFFFFF
    {0x12345678, 0x78563412},
    {0x0189ABEF, 0xEFAB8901},   
    {0xFEBA9810, 0x1098BAFE},
};

#pragma warning( pop )


//I:\bugbert.src\cqcoreutil\adutil.cpp
LONG AdSerializeLong(LONG value)
{
    LONG serializedValue = 0;
    PBYTE pBytes = (PBYTE)&serializedValue;
    int iNumberOfBytes = sizeof(value);

    // Always serialize in little endianness  in spite of the 
    // current machine's endianness, so that the serialized 
    // data can also be deserialized correctly in big endian machines
    // (deserializing is also always in little endianness).
    for (int iByte = 0; iByte < iNumberOfBytes; iByte++) {
        *(pBytes + iByte) = (BYTE)(0xFF & value);
        value >>= 8;
    }

    return serializedValue;
}

void testMethod()
{
    // Serialize into memory buf
    int len = sizeof(testValues) / sizeof(testValues[0]);
    int numberOfBytes = len * sizeof(LONG);
    PBYTE buf = new BYTE[numberOfBytes];

    for (int i = 0; i < len; i++) {
        LONG value = testValues[i][0];
        value = AdSerializeLong(value);
        memcpy(buf + (i * sizeof(LONG)), (const PBYTE)&value, sizeof(LONG));
    }   
    delete[] buf;

    
}

int main_() {

   // CListCtrl m_subscribeUsers;
    testMethod();
	return 0;
}