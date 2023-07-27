#ifndef USER_API_SERVICE
#define USER_API_SERVICE

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

            std::wstring name = ptreeResult.getData().get_child(L"name").get_value(L"Unknown");
            int money = boost::lexical_cast<int>(ptreeResult.getData().get_child(L"money").get_value(L"-1"));
            std::vector<int> tanks = asVector<int>(ptreeResult.getData(), L"tanks");

            Models::User::Info info = Info(name, money, tanks);

            return Models::DataActionResult<Models::User::Info>(Models::ErrorCode::OK, info);
        }

        Models::DataActionResult<Models::User::SignInInfo> signIn(std::wstring email, std::wstring password) override
        {
            // HttpRequest request = HttpRequest(L"/api/v1/user/signIn", HttpRequestType::POST, L"", {});

            // Models::DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

            // std::wstring name = ptreeResult.getData().get_child(L"name").get_value(L"Unknown");
            // int money = boost::lexical_cast<int>(ptreeResult.getData().get_child(L"money").get_value(L"-1"));
            // std::vector<int> tanks = asVector<int>(ptreeResult.getData(), L"tanks");

            SignInInfo info = SignInInfo(L"");

            return Models::DataActionResult<Models::User::SignInInfo>(Models::ErrorCode::OK, info);
        }

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif