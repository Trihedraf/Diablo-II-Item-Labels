#pragma once
#include <Windows.h>

void GameLoop();
LONG WINAPI GameWindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno);