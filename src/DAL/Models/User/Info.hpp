#ifndef DAL_USER_INFO
#define DAL_USER_INFO

#include "string"

namespace T10::DAL::Models::User
{
    class Info
    {
    public:
        Info(int id, const std::wstring &email, const std::wstring &name, int money, int battlesAmount, int victoriesAmount)
        {
            _id = id;
            _email = email;
            _name = name;
            _money = money;
            _battlesAmount = battlesAmount;
            _victoriesAmount = victoriesAmount;
        }

        int getId() const {
            return _id;
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
        int _id, _money, _battlesAmount, _victoriesAmount;
    };
}

#endif