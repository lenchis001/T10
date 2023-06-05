#pragma once

#include "string"
#include "map"

#include "levels/LevelType.h"

using namespace std;

namespace T10 {
	typedef void SwitchLevelCallback(LevelType type, map<wstring, wstring> params);
}