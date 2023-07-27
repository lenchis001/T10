#ifndef TANK_SERVICE
#define TANK_SERVICE

#include "ITankService.h"
#include "BLL/Services/BaseService.hpp"

#include "DAL/ApiServices/Tank/ITankApiService.h"

namespace T10::BLL::Services::Tanks
{
    class TankService : public ITankService, public BaseService
    {
    public:
        TankService(boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> tankApiService)
        {
            _tankApiService = tankApiService;
        }

        boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll()
        {
            boost::shared_ptr<DAL::Models::DataActionResult<std::vector<DAL::Models::Tanks::Tank>>> dalTankResult = _tankApiService->getAll();

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
            std::vector<Models::Tanks::Tank> bllTanks = _toBllTank(dalTankResult->getData());

            return boost::make_shared<Models::DataActionResult<std::vector<Models::Tanks::Tank>>>(bllErrorCode, bllTanks);
        }

    private:
        boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> _tankApiService;

        std::vector<Models::Tanks::Tank> _toBllTank(const std::vector<DAL::Models::Tanks::Tank> &dalTanks)
        {
            std::vector<Models::Tanks::Tank> tanks;

            for (const DAL::Models::Tanks::Tank &tank : dalTanks)
            {
                tanks.push_back(Models::Tanks::Tank(tank.getId(), tank.getName(), tank.getPrice(), tank.getHealthPoints(), tank.getDamage(), tank.getMaxSpeed(), tank.getAcceleration()));
            }

            return tanks;
        }
    };
}

#endif