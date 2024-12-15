#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

using CryptoFunc = void (*)(char*, const char);

void log(const std::string& message) {
    std::ofstream logg("sender.log", std::ios::app);
    logg << message << std::endl;
}

int main() {
    HINSTANCE hDll = LoadLibraryA("CryptDLL.dll");
    if (!hDll) {
        std::cerr << "loading lib Crypt.dll invalid" << std::endl;
        return 1;
    }
    CryptoFunc fun = (CryptoFunc)GetProcAddress(hDll, "fnCryptDLL");
    if (!fun) {
        std::cerr << "Cannot load CryptoFunc" << std::endl;
        return 1;
    }
    //WCHAR
    HANDLE hPipe = CreateFileA(".\\pipe\\MyPipe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Cannot connect to pipe" << std::endl;
        log("No connection to pipe");
        return 1;
    }
    char message[128];
    std::cout << "Message to enter: ";
    std::cin.getline(message, sizeof(message));

    fun(message, 'a');

    DWORD bWritten;
    WriteFile(hPipe, message, sizeof(message) + 1, &bWritten, NULL);

    log("Sent: " + std::string(message));

    CloseHandle(hPipe);
    FreeLibrary(hDll);
    return 0;
}