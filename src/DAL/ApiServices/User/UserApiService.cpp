#include "UserApiService.h"

#include "boost/lexical_cast.hpp"

using namespace T10::DAL::Models;
using namespace T10::DAL::Models::User;

namespace T10::DAL::ApiServices::User
{
    UserApiService::UserApiService(boost::shared_ptr<ICommunicationService> communicationService) : BaseApiService(communicationService)
    {
        _communicationService = communicationService;
    }

    Models::ActionResult<Models::User::Info> UserApiService::getInfo()
    {
        HttpRequest request = HttpRequest(L"/api/v1/user/info", HttpRequestType::GET, L"", {});

        Models::ActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

        std::wstring name = ptreeResult.getData().get_child(L"name").get_value(L"Unknown");
        int money = boost::lexical_cast<int>(ptreeResult.getData().get_child(L"money").get_value(L"-1"));
        std::vector<int> tanks = asVector<int>(ptreeResult.getData(), L"tanks");

        Models::User::Info info = Info(name, money, tanks);

        return Models::ActionResult<Models::User::Info>(Models::ErrorCode::OK, info);
    }
}