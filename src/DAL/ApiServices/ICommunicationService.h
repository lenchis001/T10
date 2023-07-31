#ifndef ICOMMUNICATION_SERVICE
#define ICOMMUNICATION_SERVICE

#include "string"

#include "DAL/Models/HttpRequest.hpp"
#include "DAL/Models/HttpResponse.hpp"

namespace T10::DAL::ApiServices
{
    class ICommunicationService
    {
    public:
        virtual Models::HttpResponse<> process(Models::HttpRequest &request) = 0;

        virtual void setAuthentication(std::wstring token) = 0;
    };
}

#endif