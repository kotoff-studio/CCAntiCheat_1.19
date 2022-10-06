#include <Windows.h>
#pragma comment(lib, "libMinHook.x86.lib")
#include "punishments.h"
#include <string>
#include "MinHook.h"
#include "Signatures.h"
//#include "detects.h"
//#include "check.h"
#include "ex_b64prov.h"
#include "ccac_hook.h"
#include "context.h"
#include "Provider.h"
//#include "hookmanager.h"
//#include "utils.h"

// TODO: This is an example of a library function
void fnCCAntiCheat()
{
	printf("STARTED!");
}
