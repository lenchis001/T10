#ifndef HTTP_REQUEST_TYPE
#define HTTP_REQUEST_TYPE

namespace T10::DAL::Models
{
    enum class HttpRequestType
    {
        GET,
        POST,
        PUT,
        // If we use DELETE, It will conflict with DELETE macro from Win32 API
        DELETE_T
    };
}

#endif