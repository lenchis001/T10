#ifndef IUSER_API_SERVICE
#define IUSER_API_SERVICE

#include "dal/models/User/Info.h"
#include "dal/models/ActionResult.h"

namespace T10::dal::api_services::User
{
    class IUserApiService
    {
    public:
        virtual models::ActionResult<models::user::Info> getInfo() = 0;
    };
}

#endif