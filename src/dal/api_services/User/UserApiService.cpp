#include "UserApiService.h"

#include "boost/lexical_cast.hpp"

using namespace T10::dal::models;
using namespace T10::dal::models::user;

namespace T10::dal::api_services::User
{
    UserApiService::UserApiService(boost::shared_ptr<ICommunicationService> communicationService) : BaseApiService(communicationService)
    {
        _communicationService = communicationService;
    }

    template <typename T>
    std::vector<T> asVector(boost::property_tree::wptree pt, boost::property_tree::wptree::key_type key)
    {
        std::vector<T> r;
        for (auto &item : pt.get_child(key))
            r.push_back(item.second.get_value<T>());
        return r;
    }

    models::ActionResult<models::user::Info> UserApiService::getInfo()
    {
        HttpRequest request = HttpRequest(L"/api/v1/user/info", HttpRequestType::GET, L"", {});

        models::ActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

        std::wstring name = ptreeResult.getData().get_child(L"name").get_value(L"Unknown");
        int money = boost::lexical_cast<int>(ptreeResult.getData().get_child(L"money").get_value(L"-1"));
        std::vector<int> tanks = asVector<int>(ptreeResult.getData(), L"tanks");

        models::user::Info info = Info(name, money, tanks);

        return models::ActionResult<models::user::Info>(models::ErrorCode::OK, info);
    }
}