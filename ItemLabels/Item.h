/**
*
* Item.h
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
#include "Module.h"
#include "ItemLabels.h"

struct UnitAny;

class Item : public Module {
	private:
		static map<std::string, Toggle> Toggles;
		void ResetPatches();
	public:

		Item() : Module("Item") {};

		void OnLoad();
		void OnUnload();

		void LoadConfig();

		void OnLoop();
		void OnKey(bool up, BYTE key, LPARAM lParam, bool* block);
		static BOOL PermShowItemsPatch1();
		static BOOL PermShowItemsPatch2();
		static BOOL PermShowItemsPatch3();

};

void PermShowItemsPatch1_ASM();
void PermShowItemsPatch2_ASM();
void PermShowItemsPatch3_ASM();
void PermShowItemsPatch4_ASM();
