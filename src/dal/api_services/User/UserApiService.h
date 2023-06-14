#ifndef USER_API_SERVICE
#define USER_API_SERVICE

#include "boost/smart_ptr.hpp"

#include "IUserApiService.h"
#include "dal/api_services/BaseApiService.h"

#include "dal/api_services/ICommunicationService.h"

namespace T10::dal::api_services::User
{
    class UserApiService : public BaseApiService, public IUserApiService
    {
    public:
        UserApiService(boost::shared_ptr<ICommunicationService> communicationService);

        models::ActionResult<models::user::Info> getInfo() override;

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif