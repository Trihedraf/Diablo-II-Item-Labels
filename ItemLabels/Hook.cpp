#include "Hook.h"

using namespace Drawing;
using namespace std;

std::list<Hook*> Hook::Hooks;

bool Hook::KeyClick(bool bUp, BYTE bKey, LPARAM lParam) {
	bool block = false;
	for (HookIterator it = Hooks.begin(); it!=Hooks.end(); ++it)
			if ((*it)->OnKey(bUp, bKey, lParam))
				block = true;
	return block;
}
