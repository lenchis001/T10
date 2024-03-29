#include "TankApiService.h"

#include "boost/lexical_cast.hpp"

using namespace T10::DAL::Models;
using namespace T10::DAL::ApiServices::Tanks;

TankApiService::TankApiService(boost::shared_ptr<ICommunicationService> communicationService)
	: BaseApiService(communicationService), _communicationService(communicationService)
{
}

boost::shared_ptr<DataActionResult<std::vector<Tanks::Tank>>> TankApiService::getAll()
{
	HttpRequest request = HttpRequest(L"/api/v1/tank", HttpRequestType::GET, L"", {});

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