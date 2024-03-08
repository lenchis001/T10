#ifndef START_BATTLE_MESSAGE
#define START_BATTLE_MESSAGE

#include "string"

#include "boost/json.hpp"

#include "Utils/Utils.h"

namespace T10::DAL::Models::MatchMaking::Response {

	class StartBattleMessage {
	public:
		StartBattleMessage(const std::wstring& mapName) {
			_mapName = mapName;
		}

		const std::wstring& getMapName() const {
			return _mapName;
		}

		static StartBattleMessage fromJson(const boost::json::object& value) {
			const auto mapName = value.at("mapName").as_string();

			return StartBattleMessage(TO_WSTRING(mapName));
		}
	private:
		std::wstring _mapName;
	};

}

#endif // START_BATTLE_MESSAGE