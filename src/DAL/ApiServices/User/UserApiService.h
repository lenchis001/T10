#ifndef USER_API_SERVICE_H
#define USER_API_SERVICE_H

#include "map"
#include "boost/smart_ptr.hpp"
#include "boost/lexical_cast.hpp"
#include "IUserApiService.h"
#include "DAL/ApiServices/BaseApiService.h"
#include "DAL/ApiServices/ICommunicationService.h"

using namespace T10::DAL::Models;
using namespace T10::DAL::Models::User;

namespace T10::DAL::ApiServices::User
{
    class UserApiService : public BaseApiService, public IUserApiService
    {
    public:
        UserApiService(boost::shared_ptr<ICommunicationService> communicationService);
        Models::DataActionResult<Models::User::Info> getInfo() override;
        Models::DataActionResult<Models::User::SignInInfo> signIn(std::wstring email, std::wstring password) override;
        Models::ActionResult isSignedIn();

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif // USER_API_SERVICE_H