#include "TankAssignmentApiService.h"

#include "boost/lexical_cast.hpp"

using namespace T10::DAL::Models;
using namespace T10::DAL::ApiServices::TankAssignment;

TankAssignmentApiService::TankAssignmentApiService(boost::shared_ptr<ICommunicationService> communicationService)
	: BaseApiService(communicationService), _communicationService(move(communicationService)) {}

boost::shared_ptr<DataActionResult<std::vector<TankAssignments::TankAssignment>>> TankAssignmentApiService::getMy()
{
	HttpRequest request = HttpRequest(L"/api/v1/tankassignment", HttpRequestType::GET, L"", {});

	DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

	std::vector<TankAssignments::TankAssignment> assignments;

	if (ptreeResult.getError() == Models::ErrorCode::OK)
	{
		for (auto& item : ptreeResult.getData())
		{
			auto id = boost::lexical_cast<int>(item.second.get_child(L"id").get_value(L"-1"));
			auto tankId = boost::lexical_cast<int>(item.second.get_child(L"tankId").get_value(L"-1"));

			assignments.push_back(TankAssignments::TankAssignment(id, tankId));
		}
	}

	return boost::make_shared<DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>>(ptreeResult.getError(), assignments);
}

boost::shared_ptr<ActionResult> TankAssignmentApiService::buy(const TankAssignments::AddTankAssignment& tankAssignment)
{
	std::map<std::wstring, boost::any> requestBodyMap;
	requestBodyMap[L"tankId"] = tankAssignment.getTankId();
	std::wstring requestBody = this->toJson(requestBodyMap);

	HttpRequest request = HttpRequest(L"/api/v1/tankassignment", HttpRequestType::POST, requestBody, { {DAL::Models::HeaderType::CONTENT_TYPE, L"application/json"} });

	DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

	return boost::make_shared<Models::ActionResult>(ptreeResult.getError());
}

boost::shared_ptr<ActionResult> TankAssignmentApiService::sell(int tankAssignmentId)
{
	HttpRequest request = HttpRequest(L"/api/v1/tankassignment?tankAssignmentId=" + std::to_wstring(tankAssignmentId), HttpRequestType::DELETE_T, L"", {});

	DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

	return boost::make_shared<Models::ActionResult>(ptreeResult.getError());
}