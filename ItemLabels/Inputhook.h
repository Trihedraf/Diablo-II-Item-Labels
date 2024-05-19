#pragma once
#include "Hook.h"

namespace Drawing {
	class Inputhook : public Hook {
		public:
			bool OnKey(bool up, BYTE key, LPARAM lParam);
	};
};