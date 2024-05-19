#pragma once
#include <map>
#include <string>
#include <Windows.h>

class Module;
using namespace std;

class ModuleManager {
	private:
		map<string, Module*> moduleList;

		void FixName(std::string& name);

	public:
		ModuleManager();
		~ModuleManager();

		// Module Management
		void Add(Module* module);
		Module* Get(string name);
		void Remove(Module* module);

		void LoadModules();
		void UnloadModules();

		__event void OnLoop();
		__event void OnKey(bool up, BYTE key, LPARAM lParam, bool* block);

};
