#ifndef BLL_USER_INFO
#define BLL_USER_INFO

#include "string"
#include "vector"

namespace T10::bll::models::user
{
    class Info
    {
    public:
        Info(const std::wstring& name, int money, const std::vector<int>& tanks);

        const std::wstring &getName() const;

        int getMoney() const;

        const std::vector<int> &getTanks() const;

    private:
        std::wstring _name;
        int _money;
        std::vector<int> _tanks;
    };
}

#endif