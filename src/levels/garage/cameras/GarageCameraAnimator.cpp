#include "GarageCameraAnimator.h"
#include "iostream"

using namespace irr;
using namespace irr::scene;

namespace T10::levels::garage::cameras
{
    bool GarageCameraAnimator::OnEvent(const SEvent &event)
    {
        return ISceneNodeAnimator::OnEvent(event);
    }

    boost::shared_ptr<ISceneNodeAnimator> GarageCameraAnimator::createClone(boost::shared_ptr<ISceneNode> node,
                                                                                boost::shared_ptr<ISceneManager> newManager)
    {
        return boost::make_shared<GarageCameraAnimator>();
    }

    void GarageCameraAnimator::animateNode(boost::shared_ptr<ISceneNode> node, u32 timeMs)
    {
    }

    bool GarageCameraAnimator::isEventReceiverEnabled() const {
        return true;
    }
}