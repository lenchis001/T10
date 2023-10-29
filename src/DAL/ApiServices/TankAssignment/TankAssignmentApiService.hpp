#ifndef TANK_ASSIGNMENT_API_SERVICE
#define TANK_ASSIGNMENT_API_SERVICE

#include "boost/smart_ptr.hpp"

#include "ITankAssignmentApiService.h"
#include "DAL/ApiServices/BaseApiService.hpp"

#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices::TankAssignment
{
	class TankAssignmentApiService : public BaseApiService, public ITankAssignmentApiService
	{
	public:
		TankAssignmentApiService(boost::shared_ptr<ICommunicationService> communicationService) : BaseApiService(communicationService)
		{
			_communicationService = communicationService;
		}

		boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy()
		{
			HttpRequest request = HttpRequest(L"/api/v1/tankassignment", HttpRequestType::GET, L"", {});

			DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

			std::vector<Models::TankAssignments::TankAssignment> assignments;

			if (ptreeResult.getError() == Models::ErrorCode::OK)
			{
				for (auto& item : ptreeResult.getData())
				{
					auto id = boost::lexical_cast<int>(item.second.get_child(L"id").get_value(L"-1"));
					auto tankId = boost::lexical_cast<int>(item.second.get_child(L"tankId").get_value(L"-1"));

					assignments.push_back(Models::TankAssignments::TankAssignment(id, tankId));
				}
			}

			return boost::make_shared<DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>>(ptreeResult.getError(), assignments);
		}

		virtual boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) {
			std::map<std::wstring, boost::any> requestBodyMap;
			requestBodyMap[L"tankId"] = tankAssignment.getTankId();
			std::wstring requestBody = this->toJson(requestBodyMap);

			HttpRequest request = HttpRequest(L"/api/v1/tankassignment", HttpRequestType::POST, requestBody, { {DAL::Models::HeaderType::CONTENT_TYPE, L"application/json"} });

			DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

			return boost::make_shared<Models::ActionResult>(ptreeResult.getError());
		}

		virtual boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId) {
			HttpRequest request = HttpRequest(L"/api/v1/tankassignment?tankAssignmentId=" + to_wstring(tankAssignmentId), HttpRequestType::DELETE_T, L"", {});

			DataActionResult<boost::property_tree::wptree> ptreeResult = processRequest(request);

			return boost::make_shared<Models::ActionResult>(ptreeResult.getError());
		}

	private:
		boost::shared_ptr<ICommunicationService> _communicationService;
	};
};

#endif // TANK_ASSIGNMENT_API_SERVICE