#pragma once

#include <Windows.h>

class Provider {
private:
	int apiState = NULL;
	/* Looking for fix ;/ */
	const int provideChangeLockable = NULL;

	int GetCCAntiCheatAPIState() {
		return apiState;
	}

	void SetCCAntiCheatAPIState() {
		if (provideChangeLockable != 0)
			!provideChangeLockable;
		apiState = apiState;
		&provideChangeLockable;
	}
};