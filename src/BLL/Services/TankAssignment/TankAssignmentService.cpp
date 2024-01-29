#include "TankAssignmentService.h"

using namespace T10;
using namespace T10::BLL::Models;
using namespace T10::BLL::Services::TankAssignment;

TankAssignmentService::TankAssignmentService(boost::shared_ptr<DAL::ApiServices::TankAssignment::ITankAssignmentApiService> tankAssignmentApiService) {
	_tankAssignmentApiService = tankAssignmentApiService;
}

boost::shared_ptr<DataActionResult<std::vector<TankAssignments::TankAssignment>>> TankAssignmentService::getMy() {
	boost::shared_ptr<DAL::Models::DataActionResult<std::vector<DAL::Models::TankAssignments::TankAssignment>>> dalTankResult = _tankAssignmentApiService->getMy();

	Models::ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
	std::vector<Models::TankAssignments::TankAssignment> bllTanks = _toBllTankAssignments(dalTankResult->getData());

	return boost::make_shared<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>>(bllErrorCode, bllTanks);
}

boost::shared_ptr<ActionResult> TankAssignmentService::buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) {
	auto dalTankAssignment = _toDalAddTankAssignment(tankAssignment);

	boost::shared_ptr<DAL::Models::ActionResult> dalResult = _tankAssignmentApiService->buy(dalTankAssignment);

	Models::ErrorCode bllErrorCode = _toBllErrorCode(dalResult->getError());

	return boost::make_shared<Models::ActionResult>(bllErrorCode);
}

boost::shared_ptr<ActionResult> TankAssignmentService::sell(int tankAssignmentId) {
	boost::shared_ptr<DAL::Models::ActionResult> dalResult = _tankAssignmentApiService->sell(tankAssignmentId);

	Models::ErrorCode bllErrorCode = _toBllErrorCode(dalResult->getError());

	return boost::make_shared<Models::ActionResult>(bllErrorCode);
}

std::vector<TankAssignments::TankAssignment> TankAssignmentService::_toBllTankAssignments(const std::vector<DAL::Models::TankAssignments::TankAssignment>& dalTankAssignments)
{
	std::vector<Models::TankAssignments::TankAssignment> tankAssignments;

	for (const auto& dalTankAssignment : dalTankAssignments)
	{
		tankAssignments.push_back(Models::TankAssignments::TankAssignment(dalTankAssignment.getId(), dalTankAssignment.getTankId()));
	}

	return tankAssignments;
}

DAL::Models::TankAssignments::AddTankAssignment TankAssignmentService::_toDalAddTankAssignment(const Models::TankAssignments::AddTankAssignment& tankAssignment)
{
	return DAL::Models::TankAssignments::AddTankAssignment(tankAssignment.getTankId());
}