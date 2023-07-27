#ifndef ILEVEL
#define ILEVEL

#include "string"
#include "map"

#include "irrlicht.h"

#include "boost/function.hpp"
#include "boost/type_traits.hpp"

#include "LevelType.h"

using namespace std;

namespace T10::Levels {
	typedef void SwitchLevelCallback(LevelType type, map<wstring, wstring> params);
	typedef boost::function<SwitchLevelCallback> SwitchLevelCallbackFunction;

	class ILevel : public irr::IEventReceiver {
	public:
		virtual void onLoadRequested() = 0;
		virtual void onUnloadRequested() = 0;
	};
}

#endif