#ifndef TANK_SERVICE
#define TANK_SERVICE

#include "ITankService.h"
#include "BLL/Services/BaseService.h"

#include "DAL/ApiServices/Tank/ITankApiService.h"

namespace T10::BLL::Services::Tanks
{
    class TankService : public ITankService, public BaseService
    {
    public:
        TankService(boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> tankApiService);

        boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll() override;

    private:
        boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> _tankApiService;

        std::vector<Models::Tanks::Tank> _toBllTank(const std::vector<DAL::Models::Tanks::Tank>& dalTanks);
    };
}

#endif