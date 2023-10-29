#ifndef __VIDEO_DRIVER_AWARE__
#define __VIDEO_DRIVER_AWARE__

#include "IReferenceCounted.h"

namespace irr::video {
	class IVideoDriver;

	template<class V = irr::video::IVideoDriver> class VideoDriverAwareMixin
	{
	public:
		VideoDriverAwareMixin(boost::shared_ptr<V> videoDriver) {
			_videoDriver = videoDriver;
		}

		boost::shared_ptr<V> getVideoDriver() {
			return _videoDriver.lock();
		}

		template<class T> boost::shared_ptr<T> getVideoDriver() {
			return boost::static_pointer_cast<T>(_videoDriver.lock());
		}

		void setVideoDriver(boost::shared_ptr<V> videoDriver) {
			_videoDriver = videoDriver;
		}
	private:
		boost::weak_ptr<V> _videoDriver;
	};

}

#endif