#ifndef BASE_SERVICE
#define BASE_SERVICE

#include "boost/smart_ptr.hpp"

#include "bll/models/ErrorCode.h"
#include "dal/models/ErrorCode.h"

namespace T10::bll::services
{
    class BaseService
    {
    protected:
        models::ErrorCode _toBllErrorCode(dal::models::ErrorCode dalErrorCode);
    };
}

#endif