#ifndef HTTP_REQUEST_TYPE
#define HTTP_REQUEST_TYPE

namespace T10::DAL::Models
{
    enum class HttpRequestType
    {
        GET,
        POST,
        PUT,
        DELETE
    };
}

#endif