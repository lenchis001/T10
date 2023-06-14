#include "Info.h"

namespace T10::dal::models::user
{
    Info::Info(const std::wstring &name, int money, const std::vector<int> &tanks)
    {
        _name = name;
        _money = money;
        _tanks = tanks;
    }

    const std::wstring &Info::getName() const
    {
        return _name;
    }

    int Info::getMoney() const
    {
        return _money;
    }

    const std::vector<int> &Info::getTanks() const
    {
        return _tanks;
    }
}