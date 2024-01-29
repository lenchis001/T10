#include "CacheAwareMixin.h"

template <class T>
void T10::BLL::Services::CacheAwareMixin<T>::clearCache()
{
	_cachedData = nullptr;
}

template <class T>
bool T10::BLL::Services::CacheAwareMixin<T>::AreCachedDataAvailable()
{
	return _cachedData;
}

template <class T>
void T10::BLL::Services::CacheAwareMixin<T>::saveToCache(boost::shared_ptr<T> data)
{
	_cachedData = move(data);
}

template <class T>
boost::shared_ptr<T> T10::BLL::Services::CacheAwareMixin<T>::getFromCache()
{
	return _cachedData;
}