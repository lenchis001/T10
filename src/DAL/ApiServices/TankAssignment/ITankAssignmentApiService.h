#ifndef ITANK_ASSIGNMENT_API_SERVICE
#define ITANK_ASSIGNMENT_API_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "DAL/Models/Tanks/Tank.hpp"
#include "DAL/Models/TankAssignments/TankAssignment.hpp"
#include "DAL/Models/TankAssignments/AddTankAssignment.hpp"
#include "DAL/Models/DataActionResult.h"

namespace T10::DAL::ApiServices::TankAssignment
{
    class ITankAssignmentApiService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy() = 0;

        virtual boost::shared_ptr<Models::ActionResult> buy(const Models::TankAssignments::AddTankAssignment& tankAssignment) = 0;

        virtual boost::shared_ptr<Models::ActionResult> sell(int tankAssignmentId) = 0;
    };
}

#endif // ITANK_ASSIGNMENT_API_SERVICE