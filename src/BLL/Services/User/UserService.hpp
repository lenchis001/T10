#ifndef USER_SERVICE
#define USER_SERVICE

#include "IUserService.h"

#include "BLL/Services/BaseService.hpp"

#include "DAL/ApiServices/User/IUserApiService.h"

namespace T10::BLL::Services::User
{
    class UserService : public IUserService, public BaseService
    {
    public:
        UserService(boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService)
        {
            _userApiService = userApiService;
        }

        boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() override
        {
            DAL::Models::DataActionResult<DAL::Models::User::Info> dalUserInfoResult = _userApiService->getInfo();

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalUserInfoResult.getError());
            Models::User::Info bllUserInfo = _toBllUserInfo(dalUserInfoResult.getData());

            return boost::make_shared<Models::DataActionResult<Models::User::Info>>(bllErrorCode, bllUserInfo);
        }

    private:
        boost::shared_ptr<DAL::ApiServices::User::IUserApiService> _userApiService;

        inline Models::User::Info _toBllUserInfo(const DAL::Models::User::Info &dalUserInfo)
        {
            return Models::User::Info(dalUserInfo.getName(), dalUserInfo.getMoney(), dalUserInfo.getTanks());
        }
    };
}

#endif