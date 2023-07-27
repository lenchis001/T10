#ifndef ITANK_API_SERVICE
#define ITANK_API_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "DAL/Models/Tanks/Tank.hpp"
#include "DAL/Models/DataActionResult.h"

namespace T10::DAL::ApiServices::Tanks
{
    class ITankApiService
    {
    public:
        virtual boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll() = 0;
    };
}

#endif