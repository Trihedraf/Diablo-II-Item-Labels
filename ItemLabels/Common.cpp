/**
*
* Common.cpp
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

#include "Common.h"
using namespace std;

std::string Trim(std::string source) {
	source = source.erase(0, source.find_first_not_of(" "));
	source = source.erase(source.find_last_not_of(" ") + 1);
	source = source.erase(0, source.find_first_not_of("\t"));
	source = source.erase(source.find_last_not_of("\t") + 1);
	return source;
}

KeyCode pCodes[] = {
	{"None", 0, "Not Set"},
	{"VK_BACK", 0x08, "Backspace"},
	{"VK_TAB", 0x09, "Tab"},
	{"VK_CLEAR", 0x0C, "Clear"},
	{"VK_RETURN", 0x0D, "Enter"},
	{"VK_SHIFT", 0x10, "Shift"},
	{"VK_CONTROL", 0x11, "Control"},
	{"VK_ALT", 0x12, "Alt"},
	{"VK_PAUSE", 0x13, "Pause"},
	{"VK_CAPSLOCK", 0x14, "Caps Lock"},
	{"VK_ESCAPE", 0x1B, "Esc"},
	{"VK_SPACE", 0x20, "Space"},
	{"VK_PAGEUP", 0x21, "Page Up"},
	{"VK_PAGEDN", 0x22, "Page Down"},
	{"VK_END", 0x23, "End"},
	{"VK_HOME", 0x24, "Home"},
	{"VK_LEFT", 0x25, "Left"},
	{"VK_UP", 0x26, "Up"},
	{"VK_RIGHT", 0x27, "Right"},
	{"VK_DOWN", 0x28, "Down"},
	{"VK_SELECT", 0x29, "Select"},
	{"VK_PRINT", 0x2A, "Print"},
	{"VK_EXECUTE", 0x2B, "Execute"},
	{"VK_SNAPSHOT", 0x2C, "Prt Scr"},
	{"VK_INSERT", 0x2D, "Insert"},
	{"VK_DELETE", 0x2E, "Delete"},
	{"VK_HELP", 0x2F, "Help"},
	{"VK_0", 0x30, "0"}, {"VK_1", 0x31, "1"}, {"VK_2", 0x32, "2"}, {"VK_3", 0x33, "3"},
	{"VK_4", 0x34, "4"}, {"VK_5", 0x35, "5"}, {"VK_6", 0x36, "6"}, {"VK_7", 0x37, "7"},
	{"VK_8", 0x38, "8"}, {"VK_9", 0x39, "9"},
	{"VK_A", 0x41, "A"}, {"VK_B", 0x42, "B"}, {"VK_C", 0x43, "C"}, {"VK_D", 0x44, "D"},
	{"VK_E", 0x45, "E"}, {"VK_F", 0x46, "F"}, {"VK_G", 0x47, "G"}, {"VK_H", 0x48, "H"},
	{"VK_I", 0x49, "I"}, {"VK_J", 0x4A, "J"}, {"VK_K", 0x4B, "K"}, {"VK_L", 0x4C, "L"},
	{"VK_M", 0x4D, "M"}, {"VK_N", 0x4E, "N"}, {"VK_O", 0x4F, "O"}, {"VK_P", 0x50, "P"},
	{"VK_Q", 0x51, "Q"}, {"VK_R", 0x52, "R"}, {"VK_S", 0x53, "S"}, {"VK_T", 0x54, "T"},
	{"VK_U", 0x55, "U"}, {"VK_V", 0x56, "V"}, {"VK_W", 0x57, "W"}, {"VK_X", 0x58, "X"},
	{"VK_Y", 0x59, "Y"}, {"VK_Z", 0x5A, "Z"},
	{"VK_NUMPAD0", 0x60, "Numpad 0"}, {"VK_NUMPAD1", 0x61, "Numpad 1"},
	{"VK_NUMPAD2", 0x62, "Numpad 2"}, {"VK_NUMPAD3", 0x63, "Numpad 3"},
	{"VK_NUMPAD4", 0x64, "Numpad 4"}, {"VK_NUMPAD5", 0x65, "Numpad 5"},
	{"VK_NUMPAD6", 0x66, "Numpad 6"}, {"VK_NUMPAD7", 0x67, "Numpad 7"},
	{"VK_NUMPAD8", 0x68, "Numpad 8"}, {"VK_NUMPAD9", 0x69, "Numpad 9"},
	{"VK_NUMPADMULTIPLY", 0x6A, "Numpad *"}, {"VK_NUMPADADD", 0x6B, "Numpad +"},
	{"VK_NUMPADSUBTRACT", 0x6D, "Numpad -"}, {"VK_NUMPADDECIMAL", 0x6E, "Numpad ."}, 
	{"VK_NUMPADDIVIDE", 0x6F, "Numpad /"},
	{"VK_F1", 0x70, "F1"}, {"VK_F2", 0x71, "F2"}, {"VK_F3", 0x72, "F3"}, {"VK_F4", 0x73, "F4"},
	{"VK_F5", 0x74, "F5"}, {"VK_F6", 0x75, "F6"}, {"VK_F7", 0x76, "F7"}, {"VK_F8", 0x77, "F8"},
	{"VK_F9", 0x78, "F9"}, {"VK_F10", 0x79, "F10"}, {"VK_F11", 0x7A, "F11"}, {"VK_F12", 0x7B, "F12"},
	{"VK_F13", 0x7C, "F13"}, {"VK_F14", 0x7D, "F14"}, {"VK_F15", 0x7E, "F15"}, {"VK_F16", 0x7F, "F16"},
	{"VK_NUMLOCK", 0x90, "Numlock"}, {"VK_SCROLL", 0x91, "Scrolllock"}, {"VK_LSHIFT", 0xA0, "Left Shift"},
	{"VK_RSHIFT", 0xA1, "Right Shift"}, {"VK_LCTRL", 0xA2, "Left Ctrl"}, {"VK_RCTRL", 0xA3, "Right Ctrl"},
	{"VK_LMENU", 0xA4, "Left Menu"}, {"VK_RMENU", 0xA5, "Right Menu"}, 
	{"VK_SEMICOLON", 0xBA, ";"}, {"VK_PLUS", 0xBB, "+"}, {"VK_COMMA", 0xBC, ","}, {"VK_MINUS", 0xBD, "-"},
	{"VK_PERIOD", 0xBE, "."}, {"VK_FORWARDSLASH", 0xBD, "/"}, {"VK_TILDE", 0xBF, "~"},
	{"VK_LEFTBRACKET", 0xDB, "["}, {"VK_BACKSLASH", 0xDC, "\\"}, {"VK_RIGHTBRACKET", 0xDD, "]"},
	{"VK_QUOTE", 0xDE, "'"}};

KeyCode GetKeyCode(const char* name) {
	for (int n = 1; n < (sizeof(pCodes) / sizeof(pCodes[0])); n++)
		if (!_stricmp(name, pCodes[n].name.c_str()))
			return pCodes[n];
	return pCodes[0];
}