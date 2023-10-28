#ifndef CACHE_AWARE_SERVICE
#define CACHE_AWARE_SERVICE

#include "boost/smart_ptr.hpp"

#include "BLL/Models/ErrorCode.h"
#include "DAL/Models/ErrorCode.h"

namespace T10::BLL::Services
{
    template <class T>
    class CacheAwareMixin
    {
    protected:
        void clearCache()
        {
            _cachedData = nullptr;
        }

        bool AreCachedDataAvailable()
        {
            return _cachedData;
        }

        void saveToCache(boost::shared_ptr<T> data)
        {
            _cachedData = move(data);
        }

        boost::shared_ptr<T> getFromCache()
        {
            return _cachedData;
        }

    private:
        boost::shared_ptr<T> _cachedData;
    };
}

#endif // CACHE_AWARE_SERVICE