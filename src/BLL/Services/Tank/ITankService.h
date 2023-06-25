#ifndef ITANK_SERVICE
#define ITANK_SERVICE

#include "vector"

#include "boost/smart_ptr.hpp"

#include "BLL/Models/Tanks/Tank.h"
#include "BLL/Models/ActionResult.h"

namespace T10::BLL::Services::Tanks
{
    class ITankService
    {
    public:
        virtual boost::shared_ptr<Models::ActionResult<std::vector<Models::Tanks::Tank>>> getAll() = 0;
    };
}

#endif