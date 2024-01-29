#ifndef TANK_API_SERVICE_H
#define TANK_API_SERVICE_H

#include "vector"

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
		boost::shared_ptr<Models::DataActionResult<std::vector<Models::Tanks::Tank>>> getAll();

	private:
		boost::shared_ptr<ICommunicationService> _communicationService;
	};
}

#endif // TANK_API_SERVICE_H