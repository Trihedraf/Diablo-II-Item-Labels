#include "ItemLabels.h"

BOOL WINAPI DllMain(HMODULE instance, DWORD reason, VOID* reserved) {
	switch(reason) {
		case DLL_PROCESS_ATTACH:
			return ItemLabels::Startup(instance, reserved);
		break;
		case DLL_PROCESS_DETACH:
			return ItemLabels::Shutdown();
		break;
	}
}