#ifndef ICOMMUNICATION_SERVICE
#define ICOMMUNICATION_SERVICE

#include "dal/models/HttpRequest.h"
#include "dal/models/HttpResponse.h"

namespace T10::dal::api_services
{
    class ICommunicationService
    {
    public:
        virtual models::HttpResponse<> process(models::HttpRequest &request) = 0;
    };
}

#endif