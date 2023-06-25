#ifndef IUSER_API_SERVICE
#define IUSER_API_SERVICE

#include "DAL/Models/User/Info.h"
#include "DAL/Models/ActionResult.h"

namespace T10::DAL::ApiServices::User
{
    class IUserApiService
    {
    public:
        virtual Models::ActionResult<Models::User::Info> getInfo() = 0;
    };
}

#endif