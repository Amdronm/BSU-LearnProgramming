#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define BUFSIZE 512

using func = void (*)(char*, const char);

bool bFlag = true;

void logg(HANDLE hFile, const char* s) {
    if (!bFlag) {
        return;
    }
    DWORD cbWritten = 0;
    WriteFile(
        hFile,
        s,
        strlen(s),
        &cbWritten,
        NULL);
}

int main(int argc, char* argv[]) {

    printf("Sender working...\n");
    system("pause");

    HANDLE hFile = CreateFileA(
        "Sender.log",
        FILE_APPEND_DATA,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (!hFile) {
        printf("Failed to create log %d\n", GetLastError());
        bFlag = false;
    }

    BOOL fSuccess;


    LPCSTR lpEvent = argv[2];
    HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS, NULL, lpEvent);

    if (hEvent == NULL) {
        printf("failed to OpenEvent %d\n", GetLastError());
    }

    logg(hFile, "\nCreated event\n");

    HINSTANCE hLib = LoadLibraryA("CryptoDLL.dll");
    if (!hLib) {
        printf("cannot load DLL %d\n", GetLastError());
        return 1;
    }

    func fun = (func)GetProcAddress(hLib, "decrypt");
    if (!fun) {
        printf("cannot load decrypt function %d.\n", GetLastError());
        return 1;
    }

    logg(hFile, "DLL loaded\n");

    LPCSTR lpsPipename = "\\\\.\\pipe\\MyPipe";

    HANDLE hPipe = CreateFileA(
        lpsPipename,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Could not open pipe. GLE=%d\n", GetLastError());
        return 1;
    }

    logg(hFile, "Connected to pipe\n");

    printf("here we connected to pipe\n");

    bool bTerminate = false;

    while (!bTerminate) {
        char message[BUFSIZE];

        printf("\"terminate\" to end, message to send:\n");
        std::string s{};
        std::getline(std::cin, s);
        strcpy_s(message, sizeof(message), s.c_str());

        if (!strcmp(message, "terminate")) {
            bTerminate = true;
        }

        printf("%s\n", message);
        fun(message, 1);

        logg(hFile, "Sending encrypted message: ");
        logg(hFile, message);
        logg(hFile, "\n");

        DWORD cbWritten = 0;
        DWORD cbToWrite = (strlen(message) + 1) * sizeof(char);
        printf("Sending %d byte message: \"%s\"\n", cbToWrite, message);

        fSuccess = WriteFile(
            hPipe,
            message,
            cbToWrite,
            &cbWritten,
            NULL);

        if (!fSuccess) {
            printf("WriteFile to pipe failed. GLE=%d\n", GetLastError());
            return 1;
        }

        SetEvent(hEvent);
    }

    logg(hFile, "End of Sender\n");

    FreeLibrary(hLib);
    CloseHandle(hEvent);
    CloseHandle(hPipe);
    CloseHandle(hFile);
	return 0;
}