#include "TankService.h"

using namespace T10::BLL::Models;
using namespace T10::BLL::Models::Tanks;

namespace T10::BLL::Services::Tanks
{
    TankService::TankService(boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> tankApiService)
    {
        _tankApiService = tankApiService;
    }

    boost::shared_ptr<DataActionResult<std::vector<Models::Tanks::Tank>>> TankService::getAll()
    {
        boost::shared_ptr<DAL::Models::DataActionResult<std::vector<DAL::Models::Tanks::Tank>>> dalTankResult = _tankApiService->getAll();

        ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
        std::vector<Tank> bllTanks = _toBllTank(dalTankResult->getData());

        return boost::make_shared<Models::DataActionResult<std::vector<Tank>>>(bllErrorCode, bllTanks);
    }

    std::vector<Tank> TankService::_toBllTank(const std::vector<DAL::Models::Tanks::Tank>& dalTanks)
    {
        std::vector<Tank> tanks;

        for(const DAL::Models::Tanks::Tank& tank: dalTanks) {
            tanks.push_back(Tank(tank.getId(), tank.getName(), tank.getPrice(), tank.getHealthPoints(), tank.getDamage(), tank.getMaxSpeed(), tank.getAcceleration()));
        }

        return tanks;
    }
}