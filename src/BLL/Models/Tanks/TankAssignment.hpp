#ifndef BLL_TANK_ASSIGNMENT
#define BLL_TANK_ASSIGNMENT

#include "string"
#include "vector"

namespace T10::BLL::Models::Tanks
{
    class TankAssignment
    {
    public:
        TankAssignment(int id, int tankId)
        {
            _id = id;
            _tankId = tankId;
        }

        int getId() const
        {
            return _id;
        }

        int getTankId() const
        {
            return _tankId;
        }

    private:
        int _tankId, _id;
    };
}

#endif