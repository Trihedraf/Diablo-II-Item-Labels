/**
 *
 * Item.cpp
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

#include "Item.h"
#include "ItemLabels.h"

#define UI_GROUND_ITEMS			0x0D

map<std::string, Toggle> Item::Toggles;

//ported to 1.13c/d from https://github.com/jieaido/d2hackmap/blob/master/PermShowItem.cpp
Patch* permShowItems1 = new Patch(Call, D2CLIENT, { 0xC3D4E, 0x1D74E }, (int)PermShowItemsPatch1_ASM, 6);
Patch* permShowItems2 = new Patch(Call, D2CLIENT, { 0xC0E9A, 0x1A89A }, (int)PermShowItemsPatch1_ASM, 6);
Patch* permShowItems3 = new Patch(Call, D2CLIENT, { 0x59483, 0x4EA13 }, (int)PermShowItemsPatch2_ASM, 6);
Patch* permShowItems4 = new Patch(Call, D2CLIENT, { 0x5908A, 0x4E61A }, (int)PermShowItemsPatch3_ASM, 6);
Patch* permShowItems5 = new Patch(Call, D2CLIENT, { 0xA6BA3, 0x63443 }, (int)PermShowItemsPatch4_ASM, 6);

using namespace Drawing;

void Item::OnLoad() {
	LoadConfig();

	permShowItems1->Install();
	permShowItems2->Install();
	permShowItems3->Install();
	permShowItems4->Install();
	permShowItems5->Install();
}

void Item::LoadConfig() {
	ItemLabels::config->ReadToggle("Always Show Items", "VK_L", true, Toggles["Always Show Items"]);
}

void Item::ResetPatches() {
	//todo figure out a way to not have to install/remove the patches onloop
	//we only remove it because one of them will break being able to not
	//target monsters with your normal show items key.
	if (Toggles["Always Show Items"].state) {
		permShowItems1->Install();
		permShowItems2->Install();
		permShowItems3->Install();
		permShowItems4->Install();
		permShowItems5->Install();
	} else {
		permShowItems1->Remove();
		permShowItems2->Remove();
		permShowItems3->Remove();
		permShowItems4->Remove();
		permShowItems5->Remove();
	}
}

void Item::OnUnload() {
	permShowItems1->Remove();
	permShowItems2->Remove();
	permShowItems3->Remove();
	permShowItems4->Remove();
	permShowItems5->Remove();
}

void Item::OnLoop() {
	ResetPatches();
}

void Item::OnKey(bool up, BYTE key, LPARAM lParam, bool* block) {
	for (map<string,Toggle>::iterator it = Toggles.begin(); it != Toggles.end(); it++) {
		if (key == (*it).second.toggle) {
			*block = true;
			if (up) {
				(*it).second.state = !(*it).second.state;
			}
			return;
		}
	}
}

//seems to force alt to be down
BOOL Item::PermShowItemsPatch1()
{
	return Toggles["Always Show Items"].state || D2CLIENT_GetUIState(UI_GROUND_ITEMS);
}

//these two seem to deal w/ fixing the inv/waypoints when alt is down
//one of them breaks being able to not hover monsters when holding alt
//e.g. if ur wwing as a barb and dont want to lock a monster u usually hold
//alt (or space or whatever u have show items bound to). this is broken with
//these patches.
BOOL Item::PermShowItemsPatch2() {
	return Toggles["Always Show Items"].state || D2CLIENT_GetUIState(UI_GROUND_ITEMS);
}

BOOL Item::PermShowItemsPatch3() {
	return Toggles["Always Show Items"].state || D2CLIENT_GetUIState(UI_GROUND_ITEMS);
}


void __declspec(naked) PermShowItemsPatch1_ASM()
{
	__asm {
		call Item::PermShowItemsPatch1
		test eax, eax
		ret
	}
}


void __declspec(naked) PermShowItemsPatch2_ASM()
{
	__asm {
		call Item::PermShowItemsPatch2
		test eax, eax
		je orgcode
		ret
		orgcode :
		mov eax, dword ptr[esp + 0x20]
			test eax, eax
			ret
	}
}


void __declspec(naked) PermShowItemsPatch3_ASM()
{
	__asm {
		push ebp
		push esi
		call Item::PermShowItemsPatch3
		test eax, eax
		pop esi
		pop ebp
		jz 	outcode
		cmp ebp, 0x20
		jge outcode
		ret
		outcode :
		add dword ptr[esp], 0x38A  //to 6FB0DD89
			ret
	}
}


void __declspec(naked) PermShowItemsPatch4_ASM()
{
	__asm {
		push eax
		call Item::PermShowItemsPatch1
		mov ecx, eax
		pop eax
		ret
	}
}
