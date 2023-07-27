#ifndef ICOMMUNICATION_SERVICE
#define ICOMMUNICATION_SERVICE

#include "DAL/Models/HttpRequest.hpp"
#include "DAL/Models/HttpResponse.hpp"

namespace T10::DAL::ApiServices
{
    class ICommunicationService
    {
    public:
        virtual Models::HttpResponse<> process(Models::HttpRequest &request) = 0;
    };
}

#endif