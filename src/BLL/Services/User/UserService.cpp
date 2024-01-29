#include "UserService.h"

using namespace T10;
using namespace T10::BLL::Models;
using namespace T10::BLL::Models::User;
using namespace T10::BLL::Services::User;

UserService::UserService(
	boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService,
	boost::shared_ptr<DAL::ApiServices::ICommunicationService> communicationService,
	boost::shared_ptr<DAL::Services::IStorageService> storageService)
{
	_userApiService = userApiService;
	_communicationService = communicationService;
	_storageService = storageService;
	_currentUserId = UNKNOWN_USER;
}

boost::shared_ptr<DataActionResult<Info>> UserService::getInfo() {
	DAL::Models::DataActionResult<DAL::Models::User::Info> dalUserInfoResult = _userApiService->getInfo();

	ErrorCode bllErrorCode = _toBllErrorCode(dalUserInfoResult.getError());
	Info bllUserInfo = _toBllUserInfo(dalUserInfoResult.getData());

	if (bllErrorCode == Models::ErrorCode::OK) {
		_currentUserId = bllUserInfo.getId();
	}

	return boost::make_shared<DataActionResult<Info>>(bllErrorCode, bllUserInfo);
}

ActionResult UserService::signIn(std::wstring email, std::wstring password) {
	DAL::Models::DataActionResult<DAL::Models::User::SignInInfo> dalSignInInfoResult = _userApiService->signIn(email, password);

	ErrorCode bllErrorCode = _toBllErrorCode(dalSignInInfoResult.getError());

	if (bllErrorCode == ErrorCode::OK)
	{
		SignInInfo signInInfo = _toBllSignInInfo(dalSignInInfoResult.getData());

		auto token = signInInfo.getToken();
		_storageService->set(TOKEN_STORAGE_KEY, token);
		_communicationService->setAuthentication(token);
	}

	return ActionResult(bllErrorCode);
}

ActionResult UserService::signIn() {
	auto token = _storageService->get(TOKEN_STORAGE_KEY);

	if (token.empty()) {
		return ActionResult(ErrorCode::UNKNOWN);
	}

	_communicationService->setAuthentication(token);

	auto dalResult = _userApiService->isSignedIn();

	auto result = ActionResult(_toBllErrorCode(dalResult.getError()));

	if (result.getError() != ErrorCode::OK) {
		_communicationService->setAuthentication(L"");
	}

	return result;
}

int UserService::getCurrentUserId() {
	if (_currentUserId == UNKNOWN_USER) {
		this->getInfo();
	}

	return _currentUserId;
}

Info UserService::_toBllUserInfo(const DAL::Models::User::Info& dalUserInfo)
{
	return Info(
		dalUserInfo.getId(),
		dalUserInfo.getEmail(),
		dalUserInfo.getName(),
		dalUserInfo.getMoney(),
		dalUserInfo.getBattlesAmount(),
		dalUserInfo.getVictoriesAmount()
	);
}

User::SignInInfo UserService::_toBllSignInInfo(const DAL::Models::User::SignInInfo& signInInfo)
{
	const std::wstring& s = signInInfo.getToken();
	return Models::User::SignInInfo(s);
}