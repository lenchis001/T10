#ifndef USER_API_SERVICE
#define USER_API_SERVICE

#include "map"

#include "boost/smart_ptr.hpp"
#include "boost/lexical_cast.hpp"

#include "IUserApiService.h"
#include "DAL/ApiServices/BaseApiService.hpp"

#include "DAL/ApiServices/ICommunicationService.h"

using namespace T10::DAL::Models;
using namespace T10::DAL::Models::User;

namespace T10::DAL::ApiServices::User
{
    class UserApiService : public BaseApiService, public IUserApiService
    {
    public:
        UserApiService(boost::shared_ptr<ICommunicationService> communicationService) : BaseApiService(communicationService)
        {
            _communicationService = communicationService;
        }

        Models::DataActionResult<Models::User::Info> getInfo() override
        {
            HttpRequest request = HttpRequest(L"/api/v1/user/info", HttpRequestType::GET, L"", {});

            Models::DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

            const boost::property_tree::wptree& data = ptreeResult.getData();
            std::wstring email = data.get_child(L"email").get_value<std::wstring>();
            std::wstring name = data.get_child(L"name").get_value<std::wstring>();
            int money = data.get_child(L"money").get_value<int>();
            int battlesAmount = data.get_child(L"battlesAmount").get_value<int>();
            int victoriesAmount = data.get_child(L"victoriesAmount").get_value<int>();

            Models::User::Info info = Info(email, name, money, battlesAmount, victoriesAmount);

            return Models::DataActionResult<Models::User::Info>(Models::ErrorCode::OK, info);
        }

        Models::DataActionResult<Models::User::SignInInfo> signIn(std::wstring email, std::wstring password) override
        {
            std::map<std::wstring, std::wstring> requestBodyMap;
            requestBodyMap[L"email"] = email;
            requestBodyMap[L"password"] = password;

            std::wstring requestBody = this->toJson(requestBodyMap);
            HttpRequest request = HttpRequest(L"/api/v1/user/signIn", HttpRequestType::POST, requestBody, {{DAL::Models::HeaderType::CONTENT_TYPE, L"application/json"}});

            Models::DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

            std::wstring token;
            if (ptreeResult.getError() == Models::ErrorCode::OK)
            {
                token = ptreeResult.getData().get_child(L"token").get_value<std::wstring>();
            }

            SignInInfo info = SignInInfo(token);

            return Models::DataActionResult<Models::User::SignInInfo>(ptreeResult.getError(), info);
        }

        virtual Models::ActionResult isSignedIn() {
            HttpRequest request = HttpRequest(L"/api/v1/user/isSignedIn", HttpRequestType::GET, L"", {});

            auto ptreeResult = processRequest(request);

            return Models::ActionResult(ptreeResult.getError());
        }

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif