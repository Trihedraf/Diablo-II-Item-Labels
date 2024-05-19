#include "Inputhook.h"

using namespace Drawing;

 bool Inputhook::OnKey(bool up, BYTE key, LPARAM lParam) {
	BYTE layout[256];
	WORD out[2];
	CHAR szChar[10];
	GetKeyboardState(layout);
	if (ToAscii(key, (lParam & 0xFF0000), layout, out, 0) == 0)
		return false;
	printf_s(szChar, sizeof(szChar), "%c", out[0]);

	return true;
 }