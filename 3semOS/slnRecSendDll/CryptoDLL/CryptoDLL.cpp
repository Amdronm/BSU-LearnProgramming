// CryptoDLL.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "CryptoDLL.h"


// This is an example of an exported variable
CRYPTODLL_API int nCryptoDLL=0;

// This is an example of an exported function.
extern "C" CRYPTODLL_API void encrypt(char* data, const char key) {
    while (*data) {
        *data++ ^= key;
    }
}

extern "C" CRYPTODLL_API void decrypt(char* data, const char key) {
    while (*data) {
        *data++ ^= key;
    }
}

// This is the constructor of a class that has been exported.
CCryptoDLL::CCryptoDLL()
{
    return;
}
