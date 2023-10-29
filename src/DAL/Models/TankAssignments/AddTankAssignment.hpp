#ifndef DAL_ADD_TANK_ASSIGNMENT
#define DAL_ADD_TANK_ASSIGNMENT

namespace T10::DAL::Models::TankAssignments
{
    class AddTankAssignment
    {
    public:
        AddTankAssignment(int tankId)
        {
            _tankId = tankId;
        }

        int getTankId() const
        {
            return _tankId;
        }

    private:
        int _tankId;
    };
}

#endif