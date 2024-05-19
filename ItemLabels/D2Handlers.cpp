#include "ItemLabels.h"

#include <iterator>


void GameLoop() {
	__raise ItemLabels::moduleManager->OnLoop();
}

LONG WINAPI GameWindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	bool blockEvent = false;

	if (!D2CLIENT_GetUIState(0x05)) {
		if (uMsg == WM_KEYDOWN) {
			if (Drawing::Hook::KeyClick(false, wParam, lParam))
				return NULL;
			__raise ItemLabels::moduleManager->OnKey(false, wParam, lParam, &blockEvent);
		}

		if (uMsg == WM_KEYUP) {
			if (Drawing::Hook::KeyClick(true, wParam, lParam))
				return NULL;
			__raise ItemLabels::moduleManager->OnKey(true, wParam, lParam, &blockEvent);
		}
	}

	return blockEvent ? NULL : (LONG)CallWindowProcA(ItemLabels::OldWNDPROC, hWnd, uMsg, wParam, lParam);
}

DWORD __declspec(naked) __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno)
{
	__asm
	{
		mov eax, ecx;
		jmp D2CLIENT_GetUiVar_I;
	}
}
