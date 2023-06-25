#ifndef BASE_SERVICE
#define BASE_SERVICE

#include "boost/smart_ptr.hpp"

#include "BLL/Models/ErrorCode.h"
#include "DAL/Models/ErrorCode.h"

namespace T10::BLL::Services
{
    class BaseService
    {
    protected:
        Models::ErrorCode _toBllErrorCode(DAL::Models::ErrorCode dalErrorCode);
    };
}

#endif