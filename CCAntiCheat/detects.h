#pragma once

#include <Windows.h>
#pragma comment(lib, "libMinHook.x86.lib")
#include "punishments.h"
#include <string>
#include "MinHook.h"
#include "Signatures.h"
#include "detects.h"
#include "check.h"
#include "ex_b64prov.h"
#include "ccac_hook.h"
#include "context.h"
#include "Provider.h"
#include "hookmanager.h"
#include "utils.h"
#define OutputToChat(a, b) 0x23318F78798

using namespace std;

DWORD Entity = *(DWORD*)0x5405A7B2A;
DWORD E_PositionClass = *(DWORD*)(Entity + 0xc40);
DWORD E_RotationClass = **(DWORD**)(Entity + 0xc98);

class EntityPosition {
public:

	float posX = *(float*)(E_PositionClass + 0x15A); // Position X value + Memory address
	float posY = *(float*)(E_PositionClass + 0x89C); // Position Y value + Memory address
	float posZ = *(float*)(E_PositionClass + 0xE99); // Position Z value + Memory address



	float rX = *(float*)(E_RotationClass + 0x008); // Rotation X value + Memory address
	float rY = *(float*)(E_RotationClass + 0x0C7); // Rotation Y value + Memory address
	float rZ = *(float*)(E_RotationClass + 0x23E); // Rotation Z value + Memory address

	float slappedPlX = *(float*)(E_PositionClass + 0x5FA);
	float slappedPlY = *(float*)(E_PositionClass + 0x3BC);
	float slappedPlZ = *(float*)(E_PositionClass + 0x7AB);

};

DWORD GetProcessByExeName(const wchar_t* ExeName)
{
	PROCESSENTRY32W pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32W);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"Error CreateToolhelp32Snapshot", L"Error!", NULL);
		return false;
	}

	if (Process32FirstW(hProcessSnap, &pe32))
	{
		do
		{
			if (_wcsicmp(pe32.szExeFile, ExeName) == 0)
			{
				CloseHandle(hProcessSnap);
				return pe32.th32ProcessID;
			}
		} while (Process32NextW(hProcessSnap, &pe32));
	}

	CloseHandle(hProcessSnap);
	return 0;
}

extern EntityPosition* pos;

SigScan scan;

uintptr_t OriginalModule = scan.GetModuleBaseAddress(L"\\java\\virtual\\minecraft\\PluginAPI.dll");

LPVOID LoadLibAddr = (LPVOID)LoadLibraryA("\\jre1.8.0_291\\bin\\server\\jvm.dll");

unsigned int ExplosionAddr = 0x0F06AB34;

unsigned int targetAddr = *(DWORD*)0x4CB04;

HANDLE hProcess = (HANDLE)GetProcessByExeName(L"javaw.exe");


DWORD previousDamage = *(DWORD*)(Entity + 0x50B);
DWORD currentDamage = *(DWORD*)(Entity + 0x115);
DWORD nextDamage = *(DWORD*)(Entity + 0x20F);

enum ChatColors
{
	CHATCOLOR_BLACK,
	CHATCOLOR_DARKRED,
	CHATCOLOR_DARKGREEN,
	CHATCOLOR_GOLD,
	CHATCOLOR_DARKGREY,
	CHATCOLOR_GREEN,
	CHATCOLOR_RED,
	CHATCOLOR_YELLOW,
	CHATCOLOR_DARKBLUE,
	CHATCOLOR_DARKAQUA,
	CHATCOLOR_DARKPURPLE,
	CHATCOLOR_GRAY,
	CHARCOLOR_BLUE,
	CHATCOLOR_AQUA,
	CHATCOLOR_LIGHTPURPLE,
	CHATCOLOR_WHITE
};

void KillAura()
{
	DWORD Killaura = scan.FindPattern("javaw.exe", "\x50\x4C\x2A\x97\x55\x14\x81\x64\x02\x57\x5B", { "xxxxxx????xxxxxx" });

	if (MH_CreateHook((void*)Killaura, LoadLibAddr, (LPVOID*)OriginalModule) && previousDamage + currentDamage == nextDamage / 10.0f)
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: KillAura Detection!");
	}
}

void Explosions()
{
	DWORD Expl = scan.FindPattern("javaw.exe", "\x52\x4F\x52\x5F\x4D\x4F\x44\x55\x4C\x45\x5F\x4E\x4F\x54\x5F\x46\x4F\x55\x4E\x44\x40\x0F\x3F\x3F", { "xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxx" });

	if (MH_CreateHook((void*)Expl, LoadLibAddr, (LPVOID*)OriginalModule) && ExplosionAddr * 10 / 50 + 40)
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: Explosions Detection!");
	}
}

void Slapper()
{
	DWORD Slap = scan.FindPattern("javaw.exe", "\x20\x20\x20\x20\x20\x20\x20\x2F\x2A\x0A\x20\x20\x31\x30\x30\x36\x36\x36\x20\x20\x39\x32\x39\x30", { "xxxxxx????xxxxxx" });

	if (MH_CreateHook((void*)Slap, LoadLibAddr, (LPVOID*)OriginalModule) && targetAddr + pos->slappedPlX == pos->slappedPlY * 10 / pos->slappedPlZ / 10)
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: Slapper Detection");
	}
}

void Impact()
{
	DWORD ImpactCheat = scan.FindPattern("javaw.exe", "\x0B\x96\xA1\x67\xE8\xA3\xD6\xE2\xA9\xE1\x49\x45\xD0\x55\x57\x2C\x64\x79\x8E\xEE\x47\xBA\xDB\xF2\x3C\xAE\xF9\x03\xDD\x63\x79\x31", { "xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxx" });

	if (MH_CreateHook((void*)ImpactCheat, LoadLibAddr, (LPVOID*)OriginalModule))
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: Impact CheatClient Detection!");
	}
}

void Aristois()
{
	DWORD aristois_pattern = scan.FindPattern("javaw.exe", "\x65\xD9\x73\xF1\x52\xB1\x53\xE4\xB9\x1D\xF8\x9F\xD3\x0E\xCE\x61\xAC\x9F\x39\x0E\xEE\xF8\x8C\x88\x35\x5C\x6A\x61\x73\x69\x25\xB9", { "xxxxxx????xxxxxx" });

	if (MH_CreateHook((void*)aristois_pattern, LoadLibAddr, (LPVOID*)OriginalModule))
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: Aristois CC Detection!");
	}
}

void FLAUNCHER_CHEAT()
{
	uintptr_t g_pOffsets = scan.FindDMAAddy(hProcess, 0x560CE4, { 0x3C, 0x6F, 0x6A });
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: FLauncher Detection!");
	}
}


void KamiBlue_DETECT()
{
	DWORD KB = scan.FindPattern("javaw.exe", "\x51\x87\x69\xCF\xAA\x1D\x44\x2B\xF3\x0E\xD0\xC7\xD6\x47\x1C\xB9", { "xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxx" });

	if (MH_CreateHook((void*)KB, LoadLibAddr, (LPVOID*)OriginalModule))
	{
		OutputToChat(CHATCOLOR_RED, "[IMPORTANT!] [CCAntiCheat] Player %bukkit_player% is suspicious. Reason: KB CC Detection!");
	}
}