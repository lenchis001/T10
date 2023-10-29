#pragma once

#ifndef __SHARED_THIS_MIXIN__
#define __SHARED_THIS_MIXIN__

#include "IReferenceCounted.h"

template<class T> class SharedThisMixin {
public:
	boost::shared_ptr<T> getSharedThis() {
#ifdef _DEBUG
		assert(!_thisWeak.expired());
#endif

		return _thisWeak.lock();
	}

	template<class C> boost::shared_ptr<C> getSharedThis() {
#ifdef _DEBUG
		assert(!_thisWeak.expired());
#endif

		return boost::static_pointer_cast<C>(_thisWeak.lock());
	}

	virtual void setWeakPtr(boost::shared_ptr<T> thisShared) {
		_thisWeak = thisShared;
	}

private:
	boost::weak_ptr<T> _thisWeak;
};

#endif