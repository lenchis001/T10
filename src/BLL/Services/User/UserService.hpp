#ifndef USER_SERVICE
#define USER_SERVICE

#include "IUserService.h"

#include "BLL/Models/User/SignInInfo.hpp"

#include "BLL/Services/BaseService.hpp"

#include "DAL/ApiServices/User/IUserApiService.h"
#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::BLL::Services::User
{
    class UserService : public IUserService, public BaseService
    {
    public:
        UserService(
            boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService,
            boost::shared_ptr<DAL::ApiServices::ICommunicationService> communicationService)
        {
            _userApiService = userApiService;
            _communicationService = communicationService;
        }

        boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() override
        {
            DAL::Models::DataActionResult<DAL::Models::User::Info> dalUserInfoResult = _userApiService->getInfo();

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalUserInfoResult.getError());
            Models::User::Info bllUserInfo = _toBllUserInfo(dalUserInfoResult.getData());

            return boost::make_shared<Models::DataActionResult<Models::User::Info>>(bllErrorCode, bllUserInfo);
        }

        virtual Models::ActionResult signIn(std::wstring email, std::wstring password)
        {
            DAL::Models::DataActionResult<DAL::Models::User::SignInInfo> dalSignInInfoResult = _userApiService->signIn(email, password);

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalSignInInfoResult.getError());

            if (bllErrorCode == BLL::Models::ErrorCode::OK)
            {
                Models::User::SignInInfo signInInfo = _toBllSignInInfo(dalSignInInfoResult.getData());

                _communicationService->setAuthentication(signInInfo.getToken());
            }

            return Models::ActionResult(Models::ErrorCode::OK);
        }

    private:
        boost::shared_ptr<DAL::ApiServices::User::IUserApiService> _userApiService;
        boost::shared_ptr<DAL::ApiServices::ICommunicationService> _communicationService;

        inline Models::User::Info _toBllUserInfo(const DAL::Models::User::Info &dalUserInfo)
        {
            return Models::User::Info(
                dalUserInfo.getEmail(),
                dalUserInfo.getName(),
                dalUserInfo.getMoney(),
                dalUserInfo.getBattlesAmount(),
                dalUserInfo.getVictoriesAmount());
        }

        inline Models::User::SignInInfo _toBllSignInInfo(const DAL::Models::User::SignInInfo &signInInfo)
        {
            const std::wstring &s = signInInfo.getToken();

            return Models::User::SignInInfo(s);
        }
    };
}

#endif