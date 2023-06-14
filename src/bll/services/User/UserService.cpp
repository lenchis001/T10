#include "UserService.h"

namespace T10::bll::services::User
{
    UserService::UserService(boost::shared_ptr<dal::api_services::User::IUserApiService> userApiService)
    {
        _userApiService = userApiService;
    }

    boost::shared_ptr<models::ActionResult<models::user::Info>> UserService::getInfo()
    {
        dal::models::ActionResult<dal::models::user::Info> dalUserInfoResult = _userApiService->getInfo();
        
        models::ErrorCode bllErrorCode = _toBllErrorCode(dalUserInfoResult.getError());
        models::user::Info bllUserInfo = _toBllUserInfo(dalUserInfoResult.getData());

        return boost::make_shared<models::ActionResult<models::user::Info>>(bllErrorCode, bllUserInfo);
    }

    models::user::Info UserService::_toBllUserInfo(dal::models::user::Info dalUserInfo)
    {
        return models::user::Info(dalUserInfo.getName(), dalUserInfo.getMoney(), dalUserInfo.getTanks());
    }
}