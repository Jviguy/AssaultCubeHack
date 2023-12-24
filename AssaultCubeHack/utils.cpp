#include "stdafx.h"
#include "utils.h"



uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* moduleName) {
    // module base address, set to 0 for error checking
	uintptr_t moduleBaseAddr = 0;
    // Creates a snapshot of all loaded modules (x86, x64) in a specific process.
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
    // Check if obtained snapshot is correct.
    if (hSnap != INVALID_HANDLE_VALUE) {
        // intiate a entry to insert entries in the iterator into.
        MODULEENTRY32 moduleEntry;
        moduleEntry.dwSize = sizeof(MODULEENTRY32);
        // Module32First, reads a module from the iterator into our specific ptr. &moduleEntry
        if (Module32First(hSnap, &moduleEntry)) {
            // While loop.
            do {
                // Compare module names.
                if (!_wcsicmp(moduleEntry.szModule, moduleName)) {
                    moduleBaseAddr = (uintptr_t)moduleEntry.modBaseAddr;
                    break;
                }
            // Next grabs the next one.
            } while (Module32Next(hSnap, &moduleEntry));
        }
    }
    CloseHandle(hSnap);
    return moduleBaseAddr;
}

HANDLE GetProcessByName(const wchar_t* process) {
    HANDLE target = 0;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        if (Process32First(hSnap, &entry)) {
            do {
                if (!_wcsicmp(entry.szExeFile, process)) {
                    target = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                    break;
                }
            } while (Process32Next(hSnap, &entry));
        }
    }
    CloseHandle(hSnap);
    return target;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}