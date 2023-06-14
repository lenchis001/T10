#ifndef HTTP_REQUEST_TYPE
#define HTTP_REQUEST_TYPE

namespace T10::dal::models
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