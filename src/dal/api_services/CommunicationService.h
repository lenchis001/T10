#ifndef COMMUNICATION_SERVICE
#define COMMUNICATION_SERVICE

#include "ICommunicationService.h"

namespace T10::dal::api_services
{
    class CommunicationService : public ICommunicationService {
    public:
        models::HttpResponse<> process(models::HttpRequest &request) override;
    };
}

#endif