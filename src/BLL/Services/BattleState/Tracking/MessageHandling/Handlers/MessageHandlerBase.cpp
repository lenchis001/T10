#include "MessageHandlerBase.h"

using namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers;

irr::core::vector3df MessageHandlerBase::_parseVector(const boost::json::object& value) {
	auto x = value.at("x").as_double();
	auto y = value.at("y").as_double();
	auto z = value.at("z").as_double();

	return irr::core::vector3df(x, y, z);
}