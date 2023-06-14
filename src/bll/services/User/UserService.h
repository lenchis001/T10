#ifndef USER_SERVICE
#define USER_SERVICE

#include "IUserService.h"

#include "bll/services/BaseService.h"

#include "dal/api_services/User/IUserApiService.h"

namespace T10::bll::services::User
{
    class UserService: public IUserService, public BaseService
    {
    public:
        UserService(boost::shared_ptr<dal::api_services::User::IUserApiService> userApiService);

        boost::shared_ptr<models::ActionResult<models::user::Info>> getInfo() override;

    private:
        boost::shared_ptr<dal::api_services::User::IUserApiService> _userApiService;

        inline models::user::Info _toBllUserInfo(dal::models::user::Info dalUserInfo);
    };
}

#endif