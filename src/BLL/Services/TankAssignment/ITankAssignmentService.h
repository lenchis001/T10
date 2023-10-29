#ifndef ITANK_ASSIGNMENT_SERVICE
#define ITANK_ASSIGNMENT_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "BLL/Models/TankAssignments/TankAssignment.hpp"
#include "BLL/Models/TankAssignments/AddTankAssignment.hpp"
#include "BLL/Models/DataActionResult.h"

namespace T10::BLL::Services::TankAssignment
{
    class ITankAssignmentService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy() = 0;

        virtual boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) = 0;

        virtual boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId) = 0;
    };
}

#endif