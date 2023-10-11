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
            std::vector<Models::Tanks::Tank> bllTanks = _toBllTanks(dalTankResult->getData());

            return boost::make_shared<Models::DataActionResult<std::vector<Models::Tanks::Tank>>>(bllErrorCode, bllTanks);
        }

        boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::TankAssignment>>> getMy()
        {
            boost::shared_ptr<DAL::Models::DataActionResult<std::vector<DAL::Models::Tanks::TankAssignment>>> dalTankResult = _tankApiService->getMy();

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
            std::vector<Models::Tanks::TankAssignment> bllTanks = _toBllTankAssignments(dalTankResult->getData());

            return boost::make_shared<Models::DataActionResult<std::vector<Models::Tanks::TankAssignment>>>(bllErrorCode, bllTanks);
        }

    private:
        boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> _tankApiService;

        std::vector<Models::Tanks::Tank> _toBllTanks(const std::vector<DAL::Models::Tanks::Tank>& dalTanks)
        {
            std::vector<Models::Tanks::Tank> tanks;

            for (const DAL::Models::Tanks::Tank& tank : dalTanks)
            {
                tanks.push_back(Models::Tanks::Tank(tank.getId(), tank.getName(), tank.getPrice(), tank.getHealthPoints(), tank.getDamage(), tank.getMaxSpeed(), tank.getAcceleration()));
            }

            return tanks;
        }

        std::vector<Models::Tanks::TankAssignment> _toBllTankAssignments(const std::vector<DAL::Models::Tanks::TankAssignment>& dalTankAssignmentss)
        {
            std::vector<Models::Tanks::TankAssignment> tankAssignments;

            for (const DAL::Models::Tanks::TankAssignment& dalTankAssignment : dalTankAssignmentss)
            {
                tankAssignments.push_back(Models::Tanks::TankAssignment(dalTankAssignment.getId(), dalTankAssignment.getTankId()));
            }

            return tankAssignments;
        }
    };
}

#endif