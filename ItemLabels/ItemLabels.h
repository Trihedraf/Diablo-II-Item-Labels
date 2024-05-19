#pragma once
#include <string>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "ModuleManager.h"
#include "Config.h"
#include "Inputhook.h"
#include "Patch.h"

using namespace std;

//boosts  hash_combine
//https://stackoverflow.com/a/19195373/597419
template <class T>
inline void hash_combine(std::size_t& s, const T& v)
{
	std::hash<T> h;
	s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

struct cGuardModule
{	
	union {
		HMODULE hModule;
		DWORD dwBaseAddress;
	};
	DWORD _1;
	char szPath[MAX_PATH];
};

namespace ItemLabels {
	extern string path;
	extern HINSTANCE instance;
	extern ModuleManager* moduleManager;
	extern Config* config;
	extern WNDPROC OldWNDPROC;
	extern bool cGuardLoaded;
	extern bool initialized;

	extern bool Startup(HINSTANCE instance, VOID* reserved);
	extern "C" __declspec(dllexport) void Initialize();
	extern bool Shutdown();
};
