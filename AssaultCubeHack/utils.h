#pragma once
#include "stdafx.h"

struct Vector3 {
	float x, y, z;
};

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* moduleName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
HANDLE GetProcessByName(const wchar_t* process);