#ifndef ITANK_ASSIGNMENT_SERVICE
#define ITANK_ASSIGNMENT_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "BLL/Models/TankAssignments/TankAssignment.hpp"
#include "BLL/Models/DataActionResult.h"

namespace T10::BLL::Services::Tanks
{
    class ITankService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll() = 0;

        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::TankAssignments::TankAssignment>>> getMy() = 0;
    };
}

#endif