#pragma once

#include <string>

using namespace std;

class CCACHook {
public:
	string getHookName();

	static int getID();

	string getHookVersion();

	bool onCheckFailure(int IntegerDefined, unsigned int ErrID);
};