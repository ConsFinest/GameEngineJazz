#include "skyBox.h"

void Skybox::onTick()
{
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> trans = ent->getComponent < Transform>();
	std::shared_ptr<Camera> cam = getEngine()->getCurrentCam().lock();
	trans->setPos(cam->getPos());
}
