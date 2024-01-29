#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "IUserService.h"
#include "BLL/Models/User/SignInInfo.hpp"
#include "BLL/Services/BaseService.h"
#include "DAL/ApiServices/User/IUserApiService.h"
#include "DAL/ApiServices/ICommunicationService.h"
#include "DAL/Services/IStorageService.h"

#define TOKEN_STORAGE_KEY L"token"
#define UNKNOWN_USER -1

namespace T10::BLL::Services::User
{
	class UserService : public IUserService, public BaseService
	{
	public:
		UserService(
			boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService,
			boost::shared_ptr<DAL::ApiServices::ICommunicationService> communicationService,
			boost::shared_ptr<DAL::Services::IStorageService> storageService);
		boost::shared_ptr<Models::DataActionResult<Models::User::Info>> getInfo() override;
		Models::ActionResult signIn(std::wstring email, std::wstring password) override;
		Models::ActionResult signIn() override;
		int getCurrentUserId();

	private:
		Models::User::Info _toBllUserInfo(const DAL::Models::User::Info& dalUserInfo);
		Models::User::SignInInfo _toBllSignInInfo(const DAL::Models::User::SignInInfo& signInInfo);

		boost::shared_ptr<DAL::ApiServices::User::IUserApiService> _userApiService;
		boost::shared_ptr<DAL::ApiServices::ICommunicationService> _communicationService;
		boost::shared_ptr<DAL::Services::IStorageService> _storageService;

		int _currentUserId;
	};
}

#endif // USER_SERVICE_H