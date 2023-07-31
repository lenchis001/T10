#ifndef DAL_USER_INFO
#define DAL_USER_INFO

#include "string"
#include "vector"

namespace T10::DAL::Models::User
{
    class Info
    {
    public:
        Info(const std::wstring &email, const std::wstring &name, int money, int battlesAmount, int victoriesAmount)
        {
            _email = email;
            _name = name;
            _money = money;
            _battlesAmount = battlesAmount;
            _victoriesAmount = victoriesAmount;
        }

        const std::wstring &getEmail() const
        {
            return _email;
        }

        const std::wstring &getName() const
        {
            return _name;
        }

        int getMoney() const
        {
            return _money;
        }

        int getBattlesAmount() const
        {
            return _battlesAmount;
        }

        int getVictoriesAmount() const
        {
            return _victoriesAmount;
        }

    private:
        std::wstring _name, _email;
        int _money, _battlesAmount, _victoriesAmount;
    };
}

#endif