#ifndef IUSER_SERVICE
#define IUSER_SERVICE

#include "boost/smart_ptr.hpp"

#include "BLL/Models/User/Info.hpp"
#include "BLL/Models/DataActionResult.h"
#include "BLL/Models/ActionResult.h"

namespace T10::BLL::Services::User
{
    class IUserService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() = 0;

        virtual Models::ActionResult signIn(std::wstring email, std::wstring password) = 0;

        virtual Models::ActionResult signIn() = 0;

        virtual int getCurrentUserId() = 0;
    };
}

#endif