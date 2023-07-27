#ifndef DAL_SIGN_IN_INFO
#define DAL_SIGN_IN_INFO

#include "string"

namespace T10::DAL::Models::User
{
    class SignInInfo
    {
    public:
        SignInInfo(std::wstring token)
        {
            _token = token;
        }

    private:
        std::wstring _token;
    };
}

#endif