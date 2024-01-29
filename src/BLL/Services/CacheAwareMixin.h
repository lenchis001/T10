#ifndef CACHE_AWARE_MIXIN_H
#define CACHE_AWARE_MIXIN_H

#include "boost/smart_ptr.hpp"

namespace T10::BLL::Services
{
	template <class T>
	class CacheAwareMixin
	{
	public:
		void clearCache();
	protected:
		bool AreCachedDataAvailable();
		void saveToCache(boost::shared_ptr<T> data);
		boost::shared_ptr<T> getFromCache();
	private:
		boost::shared_ptr<T> _cachedData;
	};
}

#endif // CACHE_AWARE_MIXIN_H