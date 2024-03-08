#ifndef DAL_ACTION_RESULT
#define DAL_ACTION_RESULT

#include "ErrorCode.h"

namespace T10::DAL::Models
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

        bool isOk() {
            return _error == ErrorCode::OK;
        }

        static ActionResult okResult() {
            return ActionResult(ErrorCode::OK);
        }

    private:
        ErrorCode _error;
    };
}

#endif