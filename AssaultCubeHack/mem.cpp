#include "stdafx.h"
#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc) {
	DWORD oldprotect;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtectEx(hProc, dst, size, oldprotect, &oldprotect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProc) {
	BYTE* nop = new BYTE[size];
	memset(nop, 0x90, size);
	PatchEx(dst, nop, size, hProc);
	delete[] nop;
}