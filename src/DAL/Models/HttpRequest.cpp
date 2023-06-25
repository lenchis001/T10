#include "HttpRequest.h"

namespace T10::DAL::Models
{
    HttpRequest::HttpRequest(
        std::wstring resource,
        HttpRequestType type,
        std::wstring body,
        std::map<std::wstring, std::wstring> headers,
        std::wstring host,
        std::wstring port)
    {
        _host = host;
        _port = port;
        _resource = resource;
        _type = type;
        _body = body;
        _headers = headers;
    }

    const std::wstring &HttpRequest::getHost() const
    {
        return _host;
    }

    const std::wstring &HttpRequest::getPort() const
    {
        return _port;
    }

    const std::wstring &HttpRequest::getResource() const {
        return _resource;
    }

    HttpRequestType HttpRequest::getType() const
    {
        return _type;
    }

    const std::wstring &HttpRequest::getBody() const
    {
        return _body;
    }

    const std::map<std::wstring, std::wstring> &HttpRequest::getHeaders() const
    {
        return _headers;
    }
}