#include "BaseService.h"

using namespace T10::BLL::Models;
using namespace T10::BLL::Services;

ErrorCode BaseService::_toBllErrorCode(DAL::Models::ErrorCode dalErrorCode)
{
	switch (dalErrorCode)
	{
	case DAL::Models::ErrorCode::OK:
		return Models::ErrorCode::OK;
	case DAL::Models::ErrorCode::UNKNOWN:
		return Models::ErrorCode::UNKNOWN;
	default:
		throw "An unknown mapping from DAL error codes";
	}
}

ActionResult BaseService::_toBllActionResult(DAL::Models::ActionResult dalActionResult) {
	auto error = _toBllErrorCode(dalActionResult.getError());

	return ActionResult(error);
}