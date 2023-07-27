#ifndef IUSER_API_SERVICE
#define IUSER_API_SERVICE

#include "string"

#include "DAL/Models/User/Info.h"
#include "DAL/Models/User/SignInInfo.hpp"
#include "DAL/Models/DataActionResult.h"

namespace T10::DAL::ApiServices::User
{
    class IUserApiService
    {
    public:
        virtual Models::DataActionResult<Models::User::Info> getInfo() = 0;

        virtual Models::DataActionResult<Models::User::SignInInfo> signIn(std::wstring email, std::wstring password) = 0;
    };
}

#endif