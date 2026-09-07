#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {

    HANDLE snapshot = CreateToolhelp32Snapshot(
        // способ обратится обьекту windows //
        TH32CS_SNAPPROCESS,
        0
    );
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cout << "ERROR\n";
        return 1;
    }
    PROCESSENTRY32 process;
    process.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(snapshot, &process)) {
        do {
            std::cout << "PID: " << process.th32ProcessID;
            std::cout << " | ";
            std::cout << "Name: " << process.szExeFile << '\n';
        } while (Process32First(snapshot, &process));
    }
    CloseHandle(snapshot);
    return 0;
}

