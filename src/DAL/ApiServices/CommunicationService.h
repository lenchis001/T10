#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

#include "map"
#include "string"

#include "boost/beast.hpp"
#include "ICommunicationService.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace T10::DAL::ApiServices
{
    class CommunicationService : public ICommunicationService
    {
    public:
        Models::HttpResponse<> process(Models::HttpRequest& request) override;
        void setAuthentication(std::wstring token);

    private:
        void _addHeaders(http::request<http::string_body>& req, const std::map<Models::HeaderType, std::wstring>& headers);
        std::wstring _token;
    };
}

#endif // COMMUNICATION_SERVICE_H