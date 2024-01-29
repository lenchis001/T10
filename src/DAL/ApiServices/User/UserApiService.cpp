#include "UserApiService.h"

using namespace T10::DAL::Models;
using namespace T10::DAL::ApiServices::User;

UserApiService::UserApiService(boost::shared_ptr<ICommunicationService> communicationService)
    : BaseApiService(communicationService), _communicationService(move(communicationService)) {}

DataActionResult<User::Info> UserApiService::getInfo()
{
    HttpRequest request = HttpRequest(L"/api/v1/user/info", HttpRequestType::GET, L"", {});

    DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

    const boost::property_tree::wptree& data = ptreeResult.getData();
    int id = data.get_child(L"id").get_value<int>();
    std::wstring email = data.get_child(L"email").get_value<std::wstring>();
    std::wstring name = data.get_child(L"name").get_value<std::wstring>();
    int money = data.get_child(L"money").get_value<int>();
    int battlesAmount = data.get_child(L"battlesAmount").get_value<int>();
    int victoriesAmount = data.get_child(L"victoriesAmount").get_value<int>();

    auto info = Models::User::Info(id, email, name, money, battlesAmount, victoriesAmount);

    return Models::DataActionResult<Models::User::Info>(Models::ErrorCode::OK, info);
}

DataActionResult<User::SignInInfo> UserApiService::signIn(std::wstring email, std::wstring password)
{
    std::map<std::wstring, boost::any> requestBodyMap;
    requestBodyMap[L"email"] = email;
    requestBodyMap[L"password"] = password;

    std::wstring requestBody = this->toJson(requestBodyMap);
    HttpRequest request = HttpRequest(L"/api/v1/user/signIn", HttpRequestType::POST, requestBody, { {DAL::Models::HeaderType::CONTENT_TYPE, L"application/json"} });

    Models::DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

    std::wstring token;
    if (ptreeResult.getError() == Models::ErrorCode::OK)
    {
        token = ptreeResult.getData().get_child(L"token").get_value<std::wstring>();
    }

    SignInInfo info = SignInInfo(token);

    return Models::DataActionResult<Models::User::SignInInfo>(ptreeResult.getError(), info);
}

ActionResult UserApiService::isSignedIn()
{
    HttpRequest request = HttpRequest(L"/api/v1/user/isSignedIn", HttpRequestType::GET, L"", {});

    auto ptreeResult = processRequest(request);

    return Models::ActionResult(ptreeResult.getError());
}