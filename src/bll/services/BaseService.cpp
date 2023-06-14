#include "BaseService.h"

namespace T10::bll::services
{
    models::ErrorCode BaseService::_toBllErrorCode(dal::models::ErrorCode dalErrorCode)
    {
        switch (dalErrorCode)
        {
        case dal::models::ErrorCode::OK:
            return models::ErrorCode::OK;
        case dal::models::ErrorCode::UNKNOWN:
            return models::ErrorCode::UNKNOWN;
        default:
            throw "An unknown mapping from DAL error codes";
        }
    }
}