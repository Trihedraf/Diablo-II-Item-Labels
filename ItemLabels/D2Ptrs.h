/**
*
* D2Ptrs.h
* BH: Copyright 2011 (C) McGod
* SlashDiablo Maphack: Copyright (C) SlashDiablo Community
*
*  This file is part of SlashDiablo Maphack.
*
*  SlashDiablo Maphack is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Affero General Public License as published
*  by the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Affero General Public License for more details.
*
*  You should have received a copy of the GNU Affero General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* This file incorporates work covered by the following copyright and
* permission notice:
*
*   ==========================================================
*   D2Ex2
*   https://github.com/lolet/D2Ex2
*   ==========================================================
*   Copyright (c) 2011-2014 Bartosz Jankowski
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*   ==========================================================
*
*/

#pragma once
// Macros adapted from lord2800's macros.
#include "Patch.h"
#include "D2Version.h"
#include "D2Handlers.h"


#ifdef _DEFINE_PTRS
#define FUNCPTR(dll, name, callingret, args, ...) \
	static Offsets f##dll##_##name##_offsets = { __VA_ARGS__ }; \
	__declspec(naked) callingret dll##_##name##args \
	{ \
		static DWORD f##dll##_##name = NULL; \
		if(f##dll##_##name == NULL) \
		{ \
		__asm { pushad } \
		f##dll##_##name = Patch::GetDllOffset(dll, *(&f##dll##_##name##_offsets._113c + D2Version::GetGameVersionID())); \
		__asm { popad } \
		} \
		__asm jmp [f##dll##_##name] \
	}
#else
#define FUNCPTR(dll, name, callingret, args, ...) extern callingret dll##_##name##args;
#endif

FUNCPTR(D2CLIENT, GetUiVar_I, DWORD __fastcall, (DWORD dwVarNo), 0xBE400, 0x17C50)

FUNCPTR(D2GFX, GetHwnd, HWND __stdcall, (void), -10048, -10007)


#undef FUNCPTR

#define D2CLIENT_GetUIState(dwVarNo)					(D2CLIENT_GetUIVar_STUB(dwVarNo))



#pragma pack(push, 1)

struct D2WinPlacement
{
	HWND hWnd;
};

