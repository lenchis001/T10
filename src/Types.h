#pragma once

#include "string"
#include "map"

#include "Levels/LevelType.h"

using namespace std;

namespace T10 {
	typedef void SwitchLevelCallback(Levels::LevelType type, map<wstring, wstring> params);
}