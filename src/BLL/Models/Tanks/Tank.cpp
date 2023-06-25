#include "Tank.h"

namespace T10::BLL::Models::Tanks
{
    Tank::Tank(int id, const std::wstring &name, int price, int healthPoints, int damage, float maxSpeed, float acceleration)
    {
        _id = id;
        _name = name;
        _price = price;
        _healthPoints = healthPoints;
        _damage = damage;
        _maxSpeed = maxSpeed;
        _acceleration = acceleration;
    }

    int Tank::getId() const
    {
        return _id;
    }

    const std::wstring &Tank::getName() const
    {
        return _name;
    }

    int Tank::getPrice() const
    {
        return _price;
    }

    int Tank::getHealthPoints() const
    {
        return _healthPoints;
    }

    int Tank::getDamage() const
    {
        return _damage;
    }

    float Tank::getMaxSpeed() const
    {
        return _maxSpeed;
    }

    float Tank::getAcceleration() const
    {
        return _acceleration;
    }
}