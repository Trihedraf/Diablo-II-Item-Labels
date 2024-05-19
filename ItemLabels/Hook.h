#pragma once
#include <list>
#include <Windows.h>

namespace Drawing {
	// HookGroups allow use of the basic hooks(Line,Text,Box,Frame)
	//	in more advanced hooks(Input,UI,Button) that require
	//	multiple basic hooks.
	class Hook;
	class HookGroup {
		public:
			std::list<Hook*> Hooks;
	};

	typedef std::list<Hook*> HookList;
	typedef std::list<Hook*>::iterator HookIterator;

	class Hook {
		private:
			static HookList Hooks;//Holds a list of every basic hook used.

		public:
			//Function gets called when someone types, return true to block the input.
			virtual bool OnKey(bool up, BYTE key, LPARAM lParam) { return false; };

			//Static function to check if we interacted with any hooks.
			static bool KeyClick(bool bUp, BYTE bKey, LPARAM lParam);
	};
};