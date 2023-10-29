#ifndef DAL_SIGN_IN_INFO
#define DAL_SIGN_IN_INFO

#include "string"

namespace T10::DAL::Models::User
{
    class SignInInfo
    {
    public:
        SignInInfo(const std::wstring& token)
        {
            _token = token;
        }

        const std::wstring& getToken() const {
            return _token;
        }

    private:
        std::wstring _token;
    };
}

#endif