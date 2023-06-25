#include "BaseService.h"

namespace T10::BLL::Services
{
    Models::ErrorCode BaseService::_toBllErrorCode(DAL::Models::ErrorCode dalErrorCode)
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
}