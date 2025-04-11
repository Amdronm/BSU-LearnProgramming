#include <Windows.h>
#include <stdio.h>

#define BUFSIZE 512

using func = void (*)(char*, const char);

bool flag = true;

void log(HANDLE hFile, const char *s) {
    if (!flag) {
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

int main() {
    HANDLE hFile = CreateFileA(
        "Receiver.log",
        FILE_APPEND_DATA,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (!hFile) {
        printf("logging file loading failed %d\n", GetLastError());
        flag = false;
    }

    HINSTANCE hLib = LoadLibraryA("CryptoDLL.dll");
    if (!hLib) {
        printf("cannot load DLL %d\n", GetLastError());
        system("pause");
        return 1;
    }

    func fun = (func)GetProcAddress(hLib, "decrypt");
    if (!fun) {
        printf("cannot load decrypt function %d.\n", GetLastError());
        return 1;
    }

    log(hFile, "\nDLL loaded\n");

    char message[BUFSIZE];

    LPCSTR lpsPipename = "\\\\.\\pipe\\MyPipe";

    HANDLE hPipe = CreateNamedPipeA(
        lpsPipename,
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE |
        PIPE_READMODE_MESSAGE |
        PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        BUFSIZE,
        BUFSIZE,
        0,
        NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Creation of pipe failed %d.\n", GetLastError());
        return 1;
    }


    printf("Server connected, creating Sender process\n");
    log(hFile, "Created Named Pipe\n");


    LPCSTR lpEventName = "{3E147BFE-36CE-46D6-BA86-42ACE9F3A924}";
    char szCommandLine[256] = { '\0', };
    sprintf_s(szCommandLine, 256, "%s %d %s", "Sender.exe", (DWORD)hPipe, lpEventName);
    DWORD dwFlags = CREATE_NEW_CONSOLE | BELOW_NORMAL_PRIORITY_CLASS;

    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    char senderTitle[] = "Sender.exe";
    si.lpTitle = senderTitle;
    PROCESS_INFORMATION pi;

    SECURITY_ATTRIBUTES saEvent = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };

    HANDLE hEvent = CreateEventA(
        &saEvent,
        FALSE,
        FALSE,
        lpEventName);

    if (hEvent == 0) {
        printf("failed to CreateEvent %d\n", GetLastError());
        return 1;
    }

    log(hFile, "Created sync event\n");

    BOOL bSuccess = CreateProcessA(
        NULL,
        szCommandLine,
        NULL,
        NULL,
        TRUE,
        dwFlags,
        NULL,
        NULL,
        &si,
        &pi);

    if (!bSuccess) {
        printf("CreateProcess failed %d\n", GetLastError());
        system("pause");
        return 1;
    }
    printf("waiting for sender until process ends\n");

    bool bTerminate = false;

    while (!bTerminate) {
        WaitForSingleObject(hEvent, INFINITE);

        log(hFile, "Now we are reading file\n");

        DWORD cbRead;
        bSuccess = ReadFile(
            hPipe,
            message,
            BUFSIZE,
            &cbRead,
            NULL);

        if (!bSuccess) {
            printf("failed to read from pipe %d", GetLastError());
            return 1;
        }
        printf("encrypted message: %s\n", message);

        fun(message, 1);
        if (!strcmp(message, "terminate")) {
            bTerminate = true;
        }

        log(hFile, "we got message: ");
        log(hFile, message);
        log(hFile, "\n");

        printf("from sender received: \n%s    \n", message);
        ResetEvent(hEvent);
    }

    system("pause");
    log(hFile, "We reached the end\n");
    FreeLibrary(hLib);
    CloseHandle(hEvent);
    CloseHandle(hPipe);
    CloseHandle(hFile);
    return 0;
}