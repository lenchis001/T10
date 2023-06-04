#pragma once

#include "string"
#include "map"

#include "Levels/LevelType.h"

using namespace std;

namespace GameLogic {
	typedef void SwitchLevelCallback(LevelType type, map<wstring, wstring> params);
}