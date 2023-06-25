#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include "string"
#include "map"

#include "HttpRequestType.h"

namespace T10::DAL::Models
{
    class HttpRequest
    {
    public:
        HttpRequest(
            std::wstring resource,
            HttpRequestType type,
            std::wstring body,
            std::map<std::wstring, std::wstring> headers,
            std::wstring host = L"localhost",
            std::wstring port = L"8087");

        const std::wstring &getHost() const;

        const std::wstring &getPort() const;

        const std::wstring &getResource() const;

        HttpRequestType getType() const;

        const std::wstring &getBody() const;

        const std::map<std::wstring, std::wstring> &getHeaders() const;

    private:
        HttpRequestType _type;
        std::wstring _host, _port, _resource, _body;
        std::map<std::wstring, std::wstring> _headers;
    };
}

#endif