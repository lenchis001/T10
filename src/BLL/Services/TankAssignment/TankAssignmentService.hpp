#ifndef TANK_ASSIGNMENT_SERVICE
#define TANK_ASSIGNMENT_SERVICE

#include "ITankAssignmentService.h"
#include "BLL/Services/BaseService.hpp"

#include "DAL/ApiServices/TankAssignment/ITankAssignmentApiService.h"

namespace T10::BLL::Services::TankAssignment
{
    class TankAssignmentService : public ITankAssignmentService, public BaseService
    {
    public:
        TankAssignmentService(boost::shared_ptr<DAL::ApiServices::TankAssignment::ITankAssignmentApiService> tankAssignmentApiService)
        {
            _tankAssignmentApiService = tankAssignmentApiService;
        }

        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy() override
        {
            boost::shared_ptr<DAL::Models::DataActionResult<std::vector<DAL::Models::TankAssignments::TankAssignment>>> dalTankResult = _tankAssignmentApiService->getMy();

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalTankResult->getError());
            std::vector<Models::TankAssignments::TankAssignment> bllTanks = _toBllTankAssignments(dalTankResult->getData());

            return boost::make_shared<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>>(bllErrorCode, bllTanks);
        }        
        
        virtual boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) override {
            auto dalTankAssignment = _toDalAddTankAssignment(tankAssignment);

            boost::shared_ptr<DAL::Models::ActionResult> dalResult = _tankAssignmentApiService->buy(dalTankAssignment);

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalResult->getError());

            return boost::make_shared<Models::ActionResult>(bllErrorCode);
        }

        virtual boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId) override {
            boost::shared_ptr<DAL::Models::ActionResult> dalResult = _tankAssignmentApiService->sell(tankAssignmentId);

            Models::ErrorCode bllErrorCode = _toBllErrorCode(dalResult->getError());

            return boost::make_shared<Models::ActionResult>(bllErrorCode);
        }

    private:
        boost::shared_ptr<DAL::ApiServices::TankAssignment::ITankAssignmentApiService> _tankAssignmentApiService;

        static std::vector<Models::TankAssignments::TankAssignment> _toBllTankAssignments(const std::vector<DAL::Models::TankAssignments::TankAssignment>& dalTankAssignmentss)
        {
            std::vector<Models::TankAssignments::TankAssignment> tankAssignments;

            for (const auto& dalTankAssignment : dalTankAssignmentss)
            {
                tankAssignments.push_back(Models::TankAssignments::TankAssignment(dalTankAssignment.getId(), dalTankAssignment.getTankId()));
            }

            return tankAssignments;
        }

        static DAL::Models::TankAssignments::AddTankAssignment _toDalAddTankAssignment(const Models::TankAssignments::AddTankAssignment& tankAssignment) {
            return DAL::Models::TankAssignments::AddTankAssignment(tankAssignment.getTankId());
        }
    };
}

#endif // TANK_ASSIGNMENT_SERVICE