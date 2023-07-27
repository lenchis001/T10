#ifndef IUSER_SERVICE
#define IUSER_SERVICE

#include "boost/smart_ptr.hpp"

#include "BLL/Models/User/Info.h"
#include "BLL/Models/DataActionResult.h"

namespace T10::BLL::Services::User
{
    class IUserService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() = 0;

        virtual boost::shared_ptr<Models::DataActionResult<
    };
}

#endif