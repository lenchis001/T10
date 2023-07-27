#ifndef USER_SERVICE
#define USER_SERVICE

#include "IUserService.h"

#include "BLL/Services/BaseService.h"

#include "DAL/ApiServices/User/IUserApiService.h"

namespace T10::BLL::Services::User
{
    class UserService: public IUserService, public BaseService
    {
    public:
        UserService(boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService);

        boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() override;

    private:
        boost::shared_ptr<DAL::ApiServices::User::IUserApiService> _userApiService;

        inline Models::User::Info _toBllUserInfo(const DAL::Models::User::Info& dalUserInfo);
    };
}

#endif