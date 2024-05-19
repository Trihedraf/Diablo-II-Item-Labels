#define _DEFINE_PTRS
#include "ItemLabels.h"
#include <Shlwapi.h>
#include <psapi.h>
#include "D2Handlers.h"
#include "ModuleManager.h"
#include "Module.h"
#include "Item.h"
#include "Task.h"

void __declspec(naked) GameLoop_Interception()
{
	__asm
	{
		pushad;
		call GameLoop;
		popad;

		pop eax;
		sub esp, 0x20;
		mov[esp + 0xC], ecx;
		push eax;
		ret;
	}
}

string ItemLabels::path;
HINSTANCE ItemLabels::instance;
ModuleManager* ItemLabels::moduleManager;
Config* ItemLabels::config;
bool ItemLabels::initialized;
bool ItemLabels::cGuardLoaded;
WNDPROC ItemLabels::OldWNDPROC;

Patch* patches[] = {
	new Patch(Call, D2CLIENT, { 0x44230, 0x45280 }, (int)GameLoop_Interception, 7),
};

unsigned int index = 0;
bool ItemLabels::Startup(HINSTANCE instance, VOID* reserved) {

	ItemLabels::instance = instance;
	if (reserved != NULL) {
		cGuardModule* pModule = (cGuardModule*)reserved;
		if (!pModule)
			return FALSE;
		path.assign(pModule->szPath);
		cGuardLoaded = true;
	}
	else {
		char szPath[MAX_PATH];
		GetModuleFileName(ItemLabels::instance, szPath, MAX_PATH);
		PathRemoveFileSpec(szPath);
		path.assign(szPath);
		path += "\\";
		cGuardLoaded = false;
	}


	initialized = false;
	Initialize();
	return true;
}

void ItemLabels::Initialize()
{
	moduleManager = new ModuleManager();
	config = new Config("ItemLabels.ini");
	if(!config->Parse()) {
		config->SetConfigName("ItemLabels.ini");
		if(!config->Parse()) {
			string msg = "Could not find ItemLabels settings.\nAttempted to load " +
				path + "ItemLabels.ini (failed).\n\nDefaults loaded.";
			MessageBox(NULL, msg.c_str(), "Failed to load BH config", MB_OK);
		}
	}

	// Do this asynchronously because D2GFX_GetHwnd() will be null if
	// we inject on process start
	Task::Enqueue([]() -> void {
		std::chrono::milliseconds duration(200);
		while(!D2GFX_GetHwnd()) {
			std::this_thread::sleep_for(duration);
		}
		ItemLabels::OldWNDPROC = (WNDPROC)GetWindowLong(D2GFX_GetHwnd(), GWL_WNDPROC);
		SetWindowLong(D2GFX_GetHwnd(), GWL_WNDPROC, (LONG)GameWindowEvent);
	});

	Task::InitializeThreadPool(2);

	new Item();

	moduleManager->LoadModules();

	// Injection would occasionally deadlock (I only ever saw it when using Tabbed Diablo
	// but theoretically it could happen during regular injection):
	// Worker thread in DllMain->LoadModules->AutoTele::OnLoad->UITab->SetCurrentTab->Lock()
	// Main thread in GameDraw->UI::OnDraw->D2WIN_SetTextSize->GetDllOffset->GetModuleHandle()
	// GetModuleHandle can invoke the loader lock which causes the deadlock, so delay patch
	// installation until after all startup initialization is done.
	for (int n = 0; n < (sizeof(patches) / sizeof(Patch*)); n++) {
		patches[n]->Install();
	}

	initialized = true;
}

bool ItemLabels::Shutdown() {
	if (initialized){
		moduleManager->UnloadModules();

		delete moduleManager;

		SetWindowLong(D2GFX_GetHwnd(), GWL_WNDPROC, (LONG)ItemLabels::OldWNDPROC);
		for (int n = 0; n < (sizeof(patches) / sizeof(Patch*)); n++) {
			delete patches[n];
		}

		delete config;
	}
	
	return true;
}
