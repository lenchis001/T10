#ifndef TANK_ASSIGNMENT_API_SERVICE_H
#define TANK_ASSIGNMENT_API_SERVICE_H

#include "boost/smart_ptr.hpp"
#include "ITankAssignmentApiService.h"
#include "DAL/ApiServices/BaseApiService.h"
#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices::TankAssignment
{
	class TankAssignmentApiService : public BaseApiService, public ITankAssignmentApiService
	{
	public:
		TankAssignmentApiService(boost::shared_ptr<ICommunicationService> communicationService);
		boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy();
		boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment);
		boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId);

	private:
		boost::shared_ptr<ICommunicationService> _communicationService;
	};
}

#endif // TANK_ASSIGNMENT_API_SERVICE_H