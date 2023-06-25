#ifndef DAL_TANK
#define DAL_TANK

#include "string"

namespace T10::DAL::Models::Tanks
{
    class Tank
    {
    public:
        Tank(int id, const std::wstring &name, int price, int healthPoints, int damage, float maxSpeed, float acceleration);

        int getId() const;

        const std::wstring &getName() const;

        int getPrice() const;

        int getHealthPoints() const;

        int getDamage() const;

        float getMaxSpeed() const;

        float getAcceleration() const;

    private:
        std::wstring _name;
        int _price, _id, _healthPoints, _damage;
        float _maxSpeed, _acceleration;
    };
}

#endif