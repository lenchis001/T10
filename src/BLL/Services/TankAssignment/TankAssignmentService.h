#ifndef TANK_ASSIGNMENT_SERVICE_H
#define TANK_ASSIGNMENT_SERVICE_H

#include "ITankAssignmentService.h"
#include "BLL/Services/BaseService.h"
#include "DAL/ApiServices/TankAssignment/ITankAssignmentApiService.h"

namespace T10::BLL::Services::TankAssignment
{
	class TankAssignmentService : public ITankAssignmentService, public BaseService
	{
	public:
		TankAssignmentService(boost::shared_ptr<DAL::ApiServices::TankAssignment::ITankAssignmentApiService> tankAssignmentApiService);
		boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy() override;
		boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) override;
		boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId) override;

	private:
		static std::vector<Models::TankAssignments::TankAssignment> _toBllTankAssignments(const std::vector<DAL::Models::TankAssignments::TankAssignment>& dalTankAssignments);
		static DAL::Models::TankAssignments::AddTankAssignment _toDalAddTankAssignment(const Models::TankAssignments::AddTankAssignment& tankAssignment);

		boost::shared_ptr<DAL::ApiServices::TankAssignment::ITankAssignmentApiService> _tankAssignmentApiService;
	};
}

#endif // TANK_ASSIGNMENT_SERVICE_H