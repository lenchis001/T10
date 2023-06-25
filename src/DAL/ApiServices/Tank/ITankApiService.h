#ifndef ITANK_API_SERVICE
#define ITANK_API_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "DAL/Models/Tanks/Tank.h"
#include "DAL/Models/ActionResult.h"

namespace T10::DAL::ApiServices::Tanks
{
    class ITankApiService
    {
    public:
        virtual boost::shared_ptr<Models::ActionResult<std::vector<Models::Tanks::Tank>>> getAll() = 0;
    };
}

#endif