#pragma once
#include <string>
#include "ModuleManager.h"

using namespace std;

class Module {
	private:
		friend class ModuleManager;

		string name;
		bool active;

		void Load();
		void Unload();

	public:
		Module(string name);

		string GetName() { return name; };
		bool IsActive() { return active; };

		virtual void OnLoad() {};
		virtual void OnUnload() {};

		virtual void OnLoop() {};
		virtual void OnKey(bool up, BYTE key, LPARAM lParam, bool* block) {}
};
