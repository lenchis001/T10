#ifndef HTTP_RESPONSE
#define HTTP_RESPONSE

#include "string"
#include "map"

namespace T10::DAL::Models
{
    template <class B = std::wstring>
    class HttpResponse
    {
    public:
        HttpResponse(int statusCode, B body, std::map<std::wstring, std::wstring> headers)
        {
            _statusCode = statusCode;
            _body = body;
            _headers = headers;
        }

        bool isOk() const
        {
            return _statusCode == 200;
        }

        int getStatusCode() const
        {
            return _statusCode;
        }

        const B &getBody() const
        {
            return _body;
        }

        const std::map<std::wstring, std::wstring> &getHeaders() const
        {
            return _headers;
        }

    private:
        int _statusCode;
        B _body;
        std::map<std::wstring, std::wstring> _headers;
    };
}

#endif