#ifndef DAL_SIGN_IN_RESULT
#define DAL_SIGN_IN_RESULT

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
    }
};

#endif