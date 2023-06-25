#ifndef COMMUNICATION_SERVICE
#define COMMUNICATION_SERVICE

#include "ICommunicationService.h"

namespace T10::DAL::ApiServices
{
    class CommunicationService : public ICommunicationService {
    public:
        Models::HttpResponse<> process(Models::HttpRequest &request) override;
    };
}

#endif