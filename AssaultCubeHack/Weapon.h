#pragma once
#include <cstdint>

class Weapon
{
public:
	int32_t ID; //0x0004
	class playerent* Owner; //0x0008
	class GunStaticInformation* StaticInfo; //0x000C
	int32_t* ReserveAmmo; //0x0010
	int32_t* MagazineAmmo; //0x0014
	int32_t* CooldownPTR; //0x0018
	int32_t AmmoFiredOutOfMagazine; //0x001C
	int32_t State; //0x0020

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	// THIS IS THE RECOIL FUNCTION.
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0024

class GunStaticInformation
{
public:
	char pad_0000[260]; //0x0000
	int16_t ShootingNoise; //0x0104
	int16_t ReloadNoise; //0x0106
	int16_t ReloadCooldown; //0x0108
	int16_t FireRateCooldown; //0x010A
	int16_t Damage; //0x010C
	int16_t SomethingWithMelee; //0x010E
	int16_t Grenade1; //0x0110
	int16_t Grenade2; //0x0112
	int16_t KnockbackLow; //0x0114
	int16_t KnockbackHigh; //0x0116
	int16_t MagSize; //0x0118
	int16_t SomethingWithUI; //0x011A
	int16_t SpreadLow; //0x011C
	int16_t SpreadHigh; //0x011E
	int16_t RecoilLow; //0x0120
	int16_t RecoilHigh; //0x0122
	int16_t SomethingWithPistolVSFullAuto; //0x0124
	int16_t Type; //0x0126
	int16_t FullAuto; //0x0128
}; //Size: 0x012A