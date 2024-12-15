// CryptDLL.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CryptDLL.h"
#include <string>


// This is an example of an exported variable
CRYPTDLL_API int nCryptDLL=0;

// This is an example of an exported function.
extern "C" CRYPTDLL_API void fnCryptDLL(char* data, const char key) {
    while (*data) {
        *data++ ^= key;
    }
}