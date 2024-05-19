#include "Module.h"
#include "ItemLabels.h"

Module::Module(string name) : name(name), active(false) {
	ItemLabels::moduleManager->Add(this);
}

void Module::Load() {
	if (IsActive())
		return;

	// Hook up all the events
	__hook(&ModuleManager::OnLoop, ItemLabels::moduleManager, &Module::OnLoop, this);
	__hook(&ModuleManager::OnKey, ItemLabels::moduleManager, &Module::OnKey, this);


	active = true;
	OnLoad();
}

void Module::Unload() {
	if (!IsActive())
		return;

	// Unhook all events
	__unhook(&ModuleManager::OnLoop, ItemLabels::moduleManager, &Module::OnLoop, this);
	__unhook(&ModuleManager::OnKey, ItemLabels::moduleManager, &Module::OnKey, this);

	active = false;
	OnUnload();
}