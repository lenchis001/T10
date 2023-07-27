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
            std::wstring port = L"8087")
        {
            _host = host;
            _port = port;
            _resource = resource;
            _type = type;
            _body = body;
            _headers = headers;
        }

        const std::wstring &getHost() const
        {
            return _host;
        }

        const std::wstring &getPort() const
        {
            return _port;
        }

        const std::wstring &getResource() const
        {
            return _resource;
        }

        HttpRequestType getType() const
        {
            return _type;
        }

        const std::wstring &getBody() const
        {
            return _body;
        }

        const std::map<std::wstring, std::wstring> &getHeaders() const
        {
            return _headers;
        }

    private:
        HttpRequestType _type;
        std::wstring _host, _port, _resource, _body;
        std::map<std::wstring, std::wstring> _headers;
    };
}

#endif