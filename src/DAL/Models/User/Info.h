#ifndef DAL_USER_INFO
#define DAL_USER_INFO

#include "string"
#include "vector"

namespace T10::DAL::Models::User
{
    class Info
    {
    public:
        Info(const std::wstring &name, int money, const std::vector<int> &tanks)
    {
        _name = name;
        _money = money;
        _tanks = tanks;
    }

    const std::wstring &getName() const
    {
        return _name;
    }

    int getMoney() const
    {
        return _money;
    }

    const std::vector<int> &getTanks() const
    {
        return _tanks;
    }

    private:
        std::wstring _name;
        int _money;
        std::vector<int> _tanks;
    };
}

#endif