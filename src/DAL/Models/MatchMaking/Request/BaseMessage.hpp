#ifndef BASE_MATCH_MAKING_DAL_MESSAGE
#define BASE_MATCH_MAKING_DAL_MESSAGE

#include "boost/json.hpp"

#include "string"

namespace T10::DAL::Models::MatchMaking::Request {

	class BaseMessage {
	public:
		virtual boost::json::object toJson() const = 0;
	protected:
		boost::json::object _toJson(const std::string& name, const boost::json::object& data) const {
			boost::json::object result;

			result["name"] = name;
			result["data"] = data;

			return result;
		}
	};

}

#endif // BASE_MATCH_MAKING_DAL_MESSAGE