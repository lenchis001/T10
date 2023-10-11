#ifndef TANK_API_SERVICE
#define TANK_API_SERVICE

#include "boost/smart_ptr.hpp"

#include "ITankApiService.h"
#include "DAL/ApiServices/BaseApiService.hpp"

#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices::Tanks
{
    class TankApiService : public BaseApiService, public ITankApiService
    {
    public:
        TankApiService(boost::shared_ptr<ICommunicationService> communicationService) : BaseApiService(communicationService)
        {
            _communicationService = communicationService;
        }

        boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll()
        {
            HttpRequest request = HttpRequest(L"/api/v1/tank/all", HttpRequestType::GET, L"", {});

            DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

            std::vector<Models::Tanks::Tank> tanks;

            if (ptreeResult.getError() == Models::ErrorCode::OK)
            {
                for (auto& item : ptreeResult.getData())
                {
                    auto id = boost::lexical_cast<int>(item.second.get_child(L"id").get_value(L"-1"));
                    auto name = item.second.get_child(L"name").get_value(L"Unknown");
                    auto price = boost::lexical_cast<int>(item.second.get_child(L"price").get_value(L"-1"));
                    auto maxSpeed = boost::lexical_cast<int>(item.second.get_child(L"maxSpeed").get_value(L"-1"));
                    auto acceleration = boost::lexical_cast<float>(item.second.get_child(L"acceleration").get_value(L"-1"));
                    auto healthPoints = boost::lexical_cast<int>(item.second.get_child(L"healthPoints").get_value(L"-1"));
                    auto damage = boost::lexical_cast<int>(item.second.get_child(L"damage").get_value(L"-1"));

                    tanks.push_back(Models::Tanks::Tank(id, name, price, healthPoints, damage, maxSpeed, acceleration));
                }
            }

            return boost::make_shared<DataActionResult<std::vector<Models::Tanks::Tank>>>(ptreeResult.getError(), tanks);
        }

        boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::TankAssignment>>> getMy()
        {
            HttpRequest request = HttpRequest(L"/api/v1/tank/my", HttpRequestType::GET, L"", {});

            DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

            std::vector<Models::Tanks::TankAssignment> assignments;

            if (ptreeResult.getError() == Models::ErrorCode::OK)
            {
                for (auto& item : ptreeResult.getData())
                {
                    auto id = boost::lexical_cast<int>(item.second.get_child(L"id").get_value(L"-1"));
                    auto tankId = boost::lexical_cast<int>(item.second.get_child(L"tankId").get_value(L"-1"));

                    assignments.push_back(Models::Tanks::TankAssignment(id, tankId));
                }
            }

            return boost::make_shared<DataActionResult<std::vector<Models::Tanks::TankAssignment>>>(ptreeResult.getError(), assignments);
        }

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif