#ifndef TANK_API_SERVICE
#define TANK_API_SERVICE

#include "boost/smart_ptr.hpp"

#include "ITankApiService.h"
#include "DAL/ApiServices/BaseApiService.h"

#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices::Tanks
{
    class TankApiService : public BaseApiService, public ITankApiService
    {
    public:
        TankApiService(boost::shared_ptr<ICommunicationService> communicationService);

        boost::shared_ptr<Models::ActionResult<std::vector<Models::Tanks::Tank>>> getAll() override;

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif