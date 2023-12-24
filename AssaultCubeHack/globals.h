#pragma once
typedef unsigned int offset;
typedef std::vector<unsigned int> offsetchain;

namespace offsets {
	// Static Offsets go here.
	offset recoil = 0x62020;
	offset ammo = 0x637E9;
	offset health = 0x0;
	offset localPlayerEnt = 0x10F4F4;
	// Dynamic or multi levels should go in seperate namespaces.
	namespace playerEnt {
		offset position = 0x0034;
		offset health = 0x00F8;
		offset armor = 0x00FC;
		offset currentWeapon = 0x0374;
		// COOL DOWNS JUST IN CASE, I NEED TO FREEZE THEM FOR A CHEAT.
		offset unknowncooldown = 0x0168;
		offset SecondaryCooldown = 0x016C;
		offset unknownCooldown = 0x0170;
		offset PrimaryCooldown = 0x0180;
		offset unknownCooldown2 = 0x0184;
		offset GernadeCooldown = 0x0188;
		offset AkimboCooldown = 0x018C;
	}
	namespace weapon {
		offset ammoPtr = 0x0014;
		offset ammo = 0;
		offset staticInfo = 0x0C;
	}
	namespace gunStaticInformation {
		offset fireRateCooldown = 0x010A;
		offset fullAuto = 0x0128;
	}
	// All chains in this namespace are assumed to be offset from the LocalPlayer, unless otherwise stated.
	namespace chains {
		offsetchain currentWeaponAmmo = {playerEnt::currentWeapon, weapon::ammoPtr, weapon::ammo};
		offsetchain currentWeaponStaticInfo = { playerEnt::currentWeapon, weapon::staticInfo, 0};
	}
}