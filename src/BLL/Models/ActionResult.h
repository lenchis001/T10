#ifndef BLL_ACTION_RESULT
#define BLL_ACTION_RESULT

#include "ErrorCode.h"

namespace T10::BLL::Models
{
    class ActionResult
    {
    public:
        ActionResult(ErrorCode error)
        {
            _error = error;
        }

        const ErrorCode getError()
        {
            return _error;
        }

    private:
        ErrorCode _error;
    };
}

#endif