#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#define ANTICHEAT_GETPLAYERS(a) 0x048FD040A
#define PUNISHMENTPLAYERNAME 0x704A
#define Bukkit_ExecuteCommand(a) 0xBB084E
// native now! #define Bukkit_GetVariable(a) 0xBB040D
#define Bukkit_ReturnResult(a) 0x09A23

using namespace std;

enum timeUnit {
	SECONDS,
	MINS,
	HOURS,
	DAYS,
	WEEKS,
	MONTHS,
	YEARS
};

int ReturnServerPlayers() {
	 int base = ANTICHEAT_GETPLAYERS(1);
	 return base;
}

bool GetPlayerName(string PlayerName) {
	int playerSource = ReturnServerPlayers();
	PlayerName = "%bukkit_player_name%";
	return true;
}

bool GetPlayerIPByNickName(string PlayerName) {
	int playerSource = ReturnServerPlayers();
	PlayerName = "%bukkit_player_name%";
	int ip = Bukkit_ExecuteCommand("%bukkit_player_name%.getAddress().getHostName();");
	return ip;
}


/*
	Ban by PlayerName
*/
bool BanPlayer(string PunishmentPlayerName, string reason, int integerTimeUnit, timeUnit textTimeUnit) {
	if (!PunishmentPlayerName.empty() && GetPlayerName("%anticheat_definedvar_detectedpl%") && !reason.empty() && integerTimeUnit != 0 && textTimeUnit != 0) {
		Bukkit_ExecuteCommand("Bukkit.getBanlist(Type.NAME).addBan(%anticheat_definedvar_detectedpl%, %reason%, %bTime% = %integerTimeUnit% + %textTimeUnit%);");
		Bukkit_ExecuteCommand("%ac_plugname%.getLogger().info(\"[CCAntiCheat] Player %anticheat_definedvar_detectedpl% was banned for %bTime% because of %reason%\");");
		Bukkit_ReturnResult("Bukkit.getBanCommandResult(ban.Id);");
		return true;
	}
	else
		return false;
	return true;
}

bool BanPlayerByIP(string PunishmentPlayerName, string reason, int integerTimeUnit, timeUnit textTimeUnit) {
	if (!PunishmentPlayerName.empty() && GetPlayerName("%anticheat_definedvar_detectedpl%") && !reason.empty() && integerTimeUnit != NULL && textTimeUnit != NULL) {
		int ip = GetPlayerIPByNickName("%anticheat_definedvar_detectedpl%"); //jconvert :/
		Bukkit_ExecuteCommand("Bukkit.getServer().banIP(%ip%.toString());"); 
		Bukkit_ExecuteCommand("%ac_plugname%.getLogger().info(\"[CCAntiCheat] Player %anticheat_definedvar_detectedpl% was IP-banned for %bTime% because of %reason%\");");
		Bukkit_ReturnResult("Bukkit.getBanIPCommandResult(banIP.Id);");
		return true;
	}
}

bool KickPlayer(string PunishmentPlayerName, string reason) {
	if (GetPlayerName("%anticheat_definedvar_detectedpl%") == true && !reason.empty()) {
		Bukkit_ExecuteCommand("Bukkit.player.kickPlayer(\"%reason%\");");
		Bukkit_ExecuteCommand("%ac_plugname%.getLogger().info(\"[CCAntiCheat] Player %anticheat_definedvar_detectedpl% was kicked. Reason: %reason%.\");");
		Bukkit_ReturnResult("Bukkit.getKickCommandResult(kick.Id);");
		return true;
	}
	else 
		return false;
	return true;
}