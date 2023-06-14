#ifndef IUSER_SERVICE
#define IUSER_SERVICE

#include "boost/smart_ptr.hpp"

#include "bll/models/User/Info.h"
#include "bll/models/ActionResult.h"

namespace T10::bll::services::User
{
    class IUserService
    {
    public:
        virtual boost::shared_ptr<models::ActionResult<models::user::Info>> getInfo() = 0;
    };
}

#endif