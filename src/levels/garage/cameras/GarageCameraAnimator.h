#include "irrlicht.h"

namespace T10::levels::garage::cameras {
    class GarageCameraAnimator: public irr::scene::ISceneNodeAnimator {
    public:
		bool OnEvent(const irr::SEvent& event) override;

        boost::shared_ptr<irr::scene::ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
				boost::shared_ptr<irr::scene::ISceneManager> newManager=0) override;

        void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override;

        bool isEventReceiverEnabled() const override;
    };
}