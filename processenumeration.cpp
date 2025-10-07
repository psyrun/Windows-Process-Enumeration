#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>  // For _TCHAR and _tprintf
#include <stdio.h>  // For _tprintf

void ListProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        _tprintf(_T("CreateToolhelp32Snapshot (of processes) failed.\n"));
        return;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);
  //handle
    // Retrieve information about the first process,
    // and exit if unsuccessful.
    if (!Process32First(hProcessSnap, &pe32)) {
        _tprintf(_T("Process32First failed.\n")); // Show cause of failure  
        CloseHandle(hProcessSnap);               // Clean the snapshot object
        return;
    }

    // Now walk the snapshot of processes, and display information about each process in turn.
    do {
        _tprintf(_T("PROCESS NAME: %s  (PID: %u)\n"), pe32.szExeFile, pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

int main(void) {
    ListProcesses();
    return 0;
}
