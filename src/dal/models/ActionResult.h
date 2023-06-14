#ifndef DAL_ACTION_RESULT
#define DAL_ACTION_RESULT

#include "ErrorCode.h"

namespace T10::dal::models
{
    template <class D>
    class ActionResult
    {
    public:
        ActionResult(ErrorCode error, D &data) : _data(data)
        {
            _error = error;
        }

        const ErrorCode getError()
        {
            return _error;
        }

        const D &getData() const
        {
            return _data;
        }

    private:
        ErrorCode _error;
        D _data;
    };
}

#endif