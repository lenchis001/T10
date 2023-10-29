#ifndef DAL_TANK
#define DAL_TANK

#include "string"

namespace T10::DAL::Models::Tanks
{
    class Tank
    {
    public:
        Tank(int id, const std::wstring &name, int price, int healthPoints, int damage, float maxSpeed, float acceleration)
        {
            _id = id;
            _name = name;
            _price = price;
            _healthPoints = healthPoints;
            _damage = damage;
            _maxSpeed = maxSpeed;
            _acceleration = acceleration;
        }

        int getId() const
        {
            return _id;
        }

        const std::wstring &getName() const
        {
            return _name;
        }

        int getPrice() const
        {
            return _price;
        }

        int getHealthPoints() const
        {
            return _healthPoints;
        }

        int getDamage() const
        {
            return _damage;
        }

        float getMaxSpeed() const
        {
            return _maxSpeed;
        }

        float getAcceleration() const
        {
            return _acceleration;
        }

    private:
        std::wstring _name;
        int _price, _id, _healthPoints, _damage;
        float _maxSpeed, _acceleration;
    };
}

#endif