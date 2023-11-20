#ifndef ICAMERA_ANIMATOR_DELEGATE
#define ICAMERA_ANIMATOR_DELEGATE

#include "irrlicht.h"

namespace T10::Levels::Cameras {
	class ICameraAnimatorDelegate {
	public:
		virtual void animateNode(irr::u32 timeMs) = 0;

		virtual bool OnEvent(const irr::SEvent& event) = 0;
	};
}

#endif // ICAMERA_ANIMATOR_DELEGATE