// AssaultCubeHack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "sdk.h"

int main()
{
    HANDLE acProc = GetProcessByName((wchar_t*)L"ac_client.exe");
    DWORD acId = GetProcessId(acProc);
    std::cout << "Found AssaultCube Process, ID: " << acId << std::endl;
    uintptr_t base_address = GetModuleBaseAddress(acId,L"ac_client.exe");
    std::cout << "Found Module Address: ";
    std::cout << std::hex << base_address << std::endl;
    if (!base_address) {
        std::cout << "ERROR";
        return 1;
    }
    uintptr_t dynamicPtrBaseAddr = base_address + offsets::localPlayerEnt;
    uintptr_t local_player_address;
    ReadProcessMemory(acProc, (void*)dynamicPtrBaseAddr, &local_player_address, sizeof(local_player_address), 0);
    bool bHealth = false, bRecoil = false, bAmmo = false;
    DWORD dwExit = 0;
    std::cout << "Cheat has started, in game loop." << std::endl;
    std::cout << "NUMPAD1: God Mode" << std::endl;
    std::cout << "NUMPAD2: Infinite Ammo" << std::endl;
    std::cout << "NUMPAD3: No Recoil" << std::endl;
    std::cout << "NUMPAD4: Toggle Current Gun Cooldown" << std::endl;
    std::cout << "NUMPAD5: Toggle Current Gun Full Auto" << std::endl;
    std::cout << "Ins: Exit Cheat" << std::endl;
    std::map<uintptr_t, int16_t> StaticWeaponToOriginalCooldown;
    while (GetExitCodeProcess(acProc, &dwExit) && dwExit == STILL_ACTIVE) {
        // HANDLE INPUTS.
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth ^= 1;
            // WILL DO THIS LATER AS I HAVEN'T LEARNED IT YET,
            // HANDLE CODE CAVING IN HERE.
            BYTE* memoryToWrite = (BYTE*)(bHealth ? "\x90\x90" : "\xFF\x0E");
            mem::PatchEx((BYTE*)(base_address + offsets::health), memoryToWrite, 2, acProc);
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bAmmo ^= 1;
            BYTE* memoryToWrite = (BYTE*)(bAmmo ? "\x90\x90" : "\xFF\x0E");
            mem::PatchEx((BYTE*)(base_address + offsets::ammo), memoryToWrite, 2, acProc);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil ^= 1;
            BYTE* memoryToWrite = (BYTE*)(bRecoil ? "\xC2\x08\x00" : "\x55\x8B\xEC");
            mem::PatchEx((BYTE*)(base_address + offsets::recoil), memoryToWrite, 3, acProc);
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
            uintptr_t addr = FindDMAAddy(acProc, dynamicPtrBaseAddr, offsets::chains::currentWeaponStaticInfo);
            addr += offsets::gunStaticInformation::fireRateCooldown;
            // if this cheat hasn't been activated for this weapon yet.
            if (StaticWeaponToOriginalCooldown.count(addr) != 1) {
                // then we should set its value in memory to be 0 and store it in the map.
                int16_t newCooldown = 10;
                int16_t oldCooldown;
                ReadProcessMemory(acProc, (void*)addr, &oldCooldown, sizeof(oldCooldown), 0);
                WriteProcessMemory(acProc, (void*)addr, &newCooldown, sizeof(newCooldown), 0);
                StaticWeaponToOriginalCooldown.insert({ addr, oldCooldown });
            } // cheat has been activated for this weapon, disable it.
            else {
                WriteProcessMemory(acProc, (void*)addr, &StaticWeaponToOriginalCooldown[addr], sizeof(int16_t), 0);
                // Make sure to remove it from the map.
                StaticWeaponToOriginalCooldown.erase(addr);
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
            uintptr_t addr = FindDMAAddy(acProc, dynamicPtrBaseAddr, offsets::chains::currentWeaponStaticInfo);
            addr += offsets::gunStaticInformation::fullAuto;
            int16_t old = 0;
            ReadProcessMemory(acProc, (void*)addr, &old, sizeof(old), 0);
            int16_t newF = old == 1 ? 0 : 1;
            WriteProcessMemory(acProc, (void*)addr, &newF, sizeof(newF), 0);
        }
        // QUIT.
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            return 0;
        }
    }
}

//current_weapon_ammo_ptr = FindDMAAddy(acProc, dynamicPtrBaseAddr, { 0x0374, 0x0014, 0 });
//std::cout << current_weapon_ammo_ptr << std::endl;
//ammo = 20;
//WriteProcessMemory(acProc, (void*)current_weapon_ammo_ptr, &ammo, sizeof(ammo), 0);

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
