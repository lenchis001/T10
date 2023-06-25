#include "UserService.h"

namespace T10::BLL::Services::User
{
    UserService::UserService(boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService)
    {
        _userApiService = userApiService;
    }

    boost::shared_ptr<Models::ActionResult<Models::User::Info>> UserService::getInfo()
    {
        DAL::Models::ActionResult<DAL::Models::User::Info> dalUserInfoResult = _userApiService->getInfo();
        
        Models::ErrorCode bllErrorCode = _toBllErrorCode(dalUserInfoResult.getError());
        Models::User::Info bllUserInfo = _toBllUserInfo(dalUserInfoResult.getData());

        return boost::make_shared<Models::ActionResult<Models::User::Info>>(bllErrorCode, bllUserInfo);
    }

    Models::User::Info UserService::_toBllUserInfo(const DAL::Models::User::Info& dalUserInfo)
    {
        return Models::User::Info(dalUserInfo.getName(), dalUserInfo.getMoney(), dalUserInfo.getTanks());
    }
}