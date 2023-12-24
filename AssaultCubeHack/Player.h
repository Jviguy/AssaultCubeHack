#pragma once
#include <cstdint>
#include "utils.h"

class playerent
{
public:
	Vector3 HeadPosition; //0x0004
	Vector3 Velocity; //0x0010
	int32_t BackAndForth; //0x001C
	int32_t LeftAndRight; //0x0020
	int32_t UpAndDown; //0x0024
	Vector3 NormalizedVelo; //0x0028
	Vector3 Position; //0x0034
	Vector3 Rotation; //0x0040
	float TriggerHeldTime; //0x004C
	char pad_0050[4]; //0x0050
	float JumpTimer; //0x0054
	char pad_0058[16]; //0x0058
	int32_t OnGround; //0x0068
	char pad_006C[4]; //0x006C
	int32_t NotShooting; //0x0070
	char pad_0074[128]; //0x0074
	void* PhysicsEntityPTR; //0x00F4
	int32_t Health; //0x00F8
	int32_t Armor; //0x00FC
	char pad_0100[12]; //0x0100
	int32_t AkimboAvailable; //0x010C
	int32_t N000000BA; //0x0110
	int32_t SecondaryAmmo; //0x0114
	char pad_0118[16]; //0x0118
	int32_t PrimaryAmmo; //0x0128
	char pad_012C[8]; //0x012C
	int32_t AkimboAmmo; //0x0134
	char pad_0138[4]; //0x0138
	int32_t SecondaryMagAmmo; //0x013C
	char pad_0140[16]; //0x0140
	int32_t PrimaryMagAmmo; //0x0150
	char pad_0154[12]; //0x0154
	int32_t GrenadeCount; //0x0160
	int32_t AkimboMagAmmo; //0x0164
	char pad_0168[4]; //0x0168
	int32_t SecondaryCooldown; //0x016C
	char pad_0170[16]; //0x0170
	int32_t PrimaryCooldown; //0x0180
	char pad_0184[4]; //0x0184
	int32_t GernadeCooldown; //0x0188
	int32_t AkimboCooldown; //0x018C
	int32_t NoClueATM; //0x0190
	int32_t SecondaryBulletsFired; //0x0194
	char pad_0198[16]; //0x0198
	int32_t PrimaryBulletsFired; //0x01A8
	char pad_01AC[8]; //0x01AC
	int32_t AkimboBulletsFired; //0x01B4
	char pad_01B8[108]; //0x01B8
	uint8_t N0000022E; //0x0224
	char PlayerName[16]; //0x0225
	char pad_0235[319]; //0x0235
	class Weapon* CurrentWeaponPTR; //0x0374
	char pad_0378[4]; //0x0378

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x037C

/*
* Cheat Engine tutorial Step 8.
* Addr = 0167AEE8, Value = 356
* (01692D20 -> 167AED0) + 18 = 167AEE8
* (085ED7C8 -> 01692D20) + 0 = 1692D20
* (01616540 -> 85ED7B0) + 18 = 85ED7C8
* "Tutorial-x86_64.exe"+325B00 -> 1616530 + 10 = 01616540
* 
* Cheat Engine Tutorial Step 9.
* Addr = 
*/

/*
* AssaultCube LocalPlayer Health multi level ptr.
* Addr = 00FBA8E0, Value = 9713
* (Base PTR -> FBA8DC) + 04 = 00FBA8E0
* "ac_client.exe"+00109B74 -> 00FBA8E0 - F8
* Local Player Static PTR = "ac_client.exe"+00109B74
* Health offset = F8.
*/