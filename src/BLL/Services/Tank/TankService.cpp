#include "TankService.h"

using namespace T10::BLL;
using namespace T10::BLL::Services::Tanks;

TankService::TankService(boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> tankApiService) {
	_tankApiService = tankApiService;
}

boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> TankService::getAll() {
	auto dalTankResult = _tankApiService->getAll();

	Models::ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
	std::vector<Models::Tanks::Tank> bllTanks = _toBllTanks(dalTankResult->getData());

	return boost::make_shared<Models::DataActionResult<std::vector<Models::Tanks::Tank>>>(bllErrorCode, bllTanks);
}

std::vector<Models::Tanks::Tank> TankService::_toBllTanks(const std::vector<DAL::Models::Tanks::Tank>& dalTanks)
{
	std::vector<Models::Tanks::Tank> tanks;

	for (const DAL::Models::Tanks::Tank& tank : dalTanks)
	{
		tanks.push_back(Models::Tanks::Tank(tank.getId(), tank.getName(), tank.getPrice(), tank.getHealthPoints(), tank.getDamage(), tank.getMaxSpeed(), tank.getAcceleration()));
	}

	return tanks;
}