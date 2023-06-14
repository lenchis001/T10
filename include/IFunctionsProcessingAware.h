#ifndef IFUNCTIONS_PROCESSING_AWARE
#define IFUNCTIONS_PROCESSING_AWARE

#include "boost/function.hpp"

#include "StandartThreadTypes.h"

typedef char ThreadType; // i hope, 128 threads will be enough for you :)
typedef boost::function<void()> QueueFunction;

class IFunctionsProcessingAware
{
public:
    virtual void addFuctionToQueue(ThreadType threadType, QueueFunction function) = 0;
};

#endif