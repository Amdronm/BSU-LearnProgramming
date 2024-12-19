#include <Windows.h>
#include <stdio.h>

#define BUFSIZE 512

using func = void (*)(char*, const char);

bool bFlag = true;

void logg(HANDLE hFile, const char* s) {
    if (!bFlag) {
        return;
    }
    DWORD cbWritten = 0;
    //printf("to logg %d bytes, message %s\n", strlen(s), s);
    WriteFile(
        hFile,
        s,
        strlen(s),
        &cbWritten,
        NULL);
    //printf("logged %d bytes\n", cbWritten);
}

int main(int argc, char* argv[]) {

    printf("Sender working... %s  \n", argv[1]);
    printf("Event name = %s\n", argv[2]);
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
        //= argv[2];
    //sscanf_s(argv[2], "%s", lpEvent, sizeof(argv[2]));
    HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS, NULL, lpEvent);

    if (hEvent == NULL) {
        printf("failed to OpenEvent %d\n", GetLastError());
    }

    logg(hFile, "\nCreated event\n");

    //WaitForSingleObject(hEvent, 10000);


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

    //DWORD dwMode = PIPE_READMODE_MESSAGE;
    //fSuccess = SetNamedPipeHandleState(
    //    hPipe,    // pipe handle 
    //    &dwMode,  // new pipe mode 
    //    NULL,     // don't set maximum bytes 
    //    NULL);    // don't set maximum time 

    //if (!fSuccess) {
    //    printf("SetNamedPipeHandleState failed. GLE=%d\n", GetLastError());
    //    return -1;
    //}

    printf("here we connected to pipe\n");

    // Send a message to the pipe server. 
    char message[BUFSIZE];

    printf("message to send:\n");
    scanf_s("%[^\n]", message, (unsigned)sizeof(message));

    printf("%s\n", message);
    fun(message, 1);

    logg(hFile, "Sending encrypted message: ");
    logg(hFile, message);
    logg(hFile, "\n");

    DWORD cbWritten = 0;
    DWORD cbToWrite = (strlen(message) + 1) * sizeof(char);
    printf("Sending %d byte message: \"%s\"\n", cbToWrite, message);

    fSuccess = WriteFile(
        hPipe,                  // pipe handle 
        message,             // message 
        cbToWrite,              // message length 
        &cbWritten,             // bytes written 
        NULL);                  // not overlapped 

    if (!fSuccess) {
        printf("WriteFile to pipe failed. GLE=%d\n", GetLastError());
        return 1;
    }

    SetEvent(hEvent);
    printf("event reseted\n");
    system("pause");
    logg(hFile, "End of Sender\n");

    FreeLibrary(hLib);
    CloseHandle(hEvent);
    CloseHandle(hPipe);
    CloseHandle(hFile);
	return 0;
}