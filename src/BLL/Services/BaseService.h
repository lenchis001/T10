#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include "boost/smart_ptr.hpp"

#include "BLL/Models/ErrorCode.h"
#include "DAL/Models/ErrorCode.h"

#include "BLL/Models/ActionResult.h"
#include "DAL/Models/ActionResult.h"

namespace T10::BLL::Services
{
	class BaseService
	{
	protected:
		Models::ErrorCode _toBllErrorCode(DAL::Models::ErrorCode dalErrorCode);

		Models::ActionResult _toBllActionResult(DAL::Models::ActionResult dalActionResult);
	};
}

#endif // BASE_SERVICE_H