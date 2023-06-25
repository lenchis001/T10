#ifndef USER_API_SERVICE
#define USER_API_SERVICE

#include "boost/smart_ptr.hpp"

#include "IUserApiService.h"
#include "DAL/ApiServices/BaseApiService.h"

#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices::User
{
    class UserApiService : public BaseApiService, public IUserApiService
    {
    public:
        UserApiService(boost::shared_ptr<ICommunicationService> communicationService);

        Models::ActionResult<Models::User::Info> getInfo() override;

    private:
        boost::shared_ptr<ICommunicationService> _communicationService;
    };
};

#endif