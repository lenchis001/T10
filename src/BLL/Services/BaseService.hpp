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
        Models::ErrorCode _toBllErrorCode(DAL::Models::ErrorCode dalErrorCode){
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
    };
}

#endif