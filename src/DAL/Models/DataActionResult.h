#ifndef DAL_DATA_ACTION_RESULT
#define DAL_DATA_ACTION_RESULT

#include "ErrorCode.h"
#include "ActionResult.h"

namespace T10::DAL::Models
{
    template <class D>
    class DataActionResult : public ActionResult
    {
    public:
        DataActionResult(ErrorCode error, D &data) : ActionResult(error), _data(data)
        {
        }

        const D &getData() const
        {
            return _data;
        }

    private:
        D _data;
    };
}

#endif