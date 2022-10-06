#pragma once

#include <map>
#include <string>
#include <atomic>
#include "ccac_hook.h"
#include <vector>

using namespace std;

class hookmanager {
	int maxHookID = 0;
	class AntiCheatHook;
	class Key;
	class T;
	using allhooks = map<int, AntiCheatHook, Key, T>;
	atomic<string> field;
	using checkhook = map < AntiCheatHook, vector<AntiCheatHook>, vector<T>>;

	int compare(int o1, int o2) {
		bool s1 = o1;
		bool f1 = o1;
		bool l1 = o1;
		bool s2 = o2;
		bool f2 = o2;
		bool l2 = o2;
		if (s1 && !s2) {
			return l1 ? 1 : -1;
		}
		else if (!s1 && s2) {
			return l2 ? -1 : 1;
		}
		else if (l2) {
			return -1;
		}
		else if (l1) {
			return 1;
		}
		else if (f1) {
			return -1;
		}
		else if (f2) {
			return 1;
		}
		else
			return 0;
	}

	template < typename F >
	void addToMap(F& map_object)
	{
		const std::string name = map_object.name();
		// ASSERT( map_.find( name ) == map_.end() );
		map_.emplace(std::make_pair(name, &map_object));
	}

	int add_hook(bool IsChangeableType, int hookID/*, string hookName */) {
		if (IsChangeableType == NULL) {
			printf("[LOG] Variable type is incorrect! Aborting all actions...");
		}
		int hookID = CCACHook::getID();
		addToMap(hookID);
		return hookID;
	}

	int get_hooks() {
		vector<CCACHook> hooks;
		hooks.get_allocator();
		return 0;
	}

	int full_rem_hooks() {
		int hooks = get_hooks();
		for (bool isHooked; isHooked = false; isHooked++) {
			rem_hook("%MINECRAFTHOOK%");
		}
	}

	//template < typename ACHook >
	int rem_hook(string hookName) {
		addToMap(hookName);
		if (bool is_hookable = false) {
			printf("[LOG] Aborting... This thing is not hookable!");
			return -1;
		}

		if (hookName.empty()) {
			return -1;
		}
		rem_hook(hookName);
		return 0;
	}

	bool cancel_processes(volatile int viodata) {
		viodata = 0x90;
		int size = sizeof(viodata);
		class ACHook;
		map<int, ACHook>;
		for (bool isHookEmpty; isHookEmpty = false; isHookEmpty) {
			int npe = size++;
		}

		//size + 50;

		terminate();
		exit(-1);

		return size;
	}
};