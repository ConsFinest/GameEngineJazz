#include <iostream>

#define STB_IMAGE_IMPLEMENTATION


#include <GameEngine/engine.h>
#include <GameEngine/component.h>
#include <GameEngine/entity.h>
#include <GameEngine/renderer.h>
#include <GameEngine/transform.h>
#include <GameEngine/camera.h>
#include <GameEngine/PBR.h>
#include <memory>


int main()
{

	std::shared_ptr<Engine> engine = Engine::intialize();
	std::shared_ptr<Entity> entity = engine->addEntity();
	std::shared_ptr<Entity> camEnt = engine->addEntity();
	std::shared_ptr<Entity> camEnt1 = engine->addEntity();
	std::shared_ptr<Entity> camEnt2 = engine->addEntity();
	std::shared_ptr<Entity> camEnt3 = engine->addEntity();
	std::shared_ptr<Entity> camEnt4 = engine->addEntity();
	std::shared_ptr<Entity> camEnt5 = engine->addEntity();
	std::shared_ptr<Entity> camEnt6 = engine->addEntity();

	std::shared_ptr<Entity> entity1 = engine->addEntity();
	std::shared_ptr<Transform> trans = camEnt->addComponent<Transform>();
	std::shared_ptr<Transform> trans1 = camEnt1->addComponent<Transform>();
	std::shared_ptr<Transform> trans2 = camEnt2->addComponent<Transform>();
	std::shared_ptr<Transform> trans3 = camEnt3->addComponent<Transform>();
	std::shared_ptr<Transform> trans4 = camEnt4->addComponent<Transform>();
	std::shared_ptr<Transform> trans5 = camEnt5->addComponent<Transform>();
	std::shared_ptr<Transform> trans6 = camEnt6->addComponent<Transform>();

	
	trans->setPos(glm::vec3(0, 0, 5));
	trans1->setPos(glm::vec3(0, 0, 0));
	trans2->setPos(glm::vec3(0, 0, 0));
	trans3->setPos(glm::vec3(0, 0, 0));
	trans4->setPos(glm::vec3(0, 0, 0));
	trans5->setPos(glm::vec3(0, 0, 0));
	trans6->setPos(glm::vec3(0, 0, 0));
	
	std::shared_ptr<Transform> transform = entity->addComponent<Transform>(glm::vec3(0, -1, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Transform> transform1 = entity1->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(45, 90, 0), glm::vec3(1.0f, 1.0f, 1.0f));

	std::shared_ptr<Camera> cam = camEnt->addComponent<Camera>();
	std::shared_ptr<Camera> cam1 = camEnt1->addComponent<Camera>();
	std::shared_ptr<Camera> cam2 = camEnt2->addComponent<Camera>();
	std::shared_ptr<Camera> cam3 = camEnt3->addComponent<Camera>();
	std::shared_ptr<Camera> cam4 = camEnt4->addComponent<Camera>();
	std::shared_ptr<Camera> cam5 = camEnt5->addComponent<Camera>();
	std::shared_ptr<Camera> cam6 = camEnt6->addComponent<Camera>();

	cam->cameraInit(60);
	cam1->cameraInit(60);
	cam2->cameraInit(60);
	cam3->cameraInit(60);
	cam4->cameraInit(60);
	cam5->cameraInit(60);
	cam6->cameraInit(60);

	cam1->setRendText();
	cam1->getEntity()->getComponent<Transform>()->setRot({ 0, 0, 0 });
	cam2->setRendText();
	cam2->getEntity()->getComponent<Transform>()->setRot({ 90, 0, 0 });
	cam3->setRendText();
	cam3->getEntity()->getComponent<Transform>()->setRot({ -90, 0, 0 });
	cam4->setRendText();
	cam4->getEntity()->getComponent<Transform>()->setRot({ 0, 90, 0 });
	cam5->setRendText();
	cam5->getEntity()->getComponent<Transform>()->setRot({ 0, 180, 0 });
	cam6->setRendText();
	cam6->getEntity()->getComponent<Transform>()->setRot({ 0, -90, 0 });


	//add entity
	//add renderer
	//on renderer set Texture to be Cam2->getRenderText
	//6 cameras
	//6 diffent views
	//bind to cubemap 
	//make cube

	std::shared_ptr<Renderer> rend = entity->addComponent<Renderer>();
	std::shared_ptr<Renderer> rend1 = entity1->addComponent<Renderer>();

	//rend->setCamera(cam);
	//rend1->setCamera(cam);

	//rend->rendererInit("../shader/Shader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");
	rend->rendererInitPBR("../shader/PBRshader.txt", "../samples/PBRsphere/pbrSphere.obj", "../samples/PBRsphere/basecolor.png","../samples/PBRsphere/basecolor.png", "../samples/PBRsphere/normal.png", "../samples/PBRsphere/metallic.png", "../samples/PBRsphere/roughness.png", "../samples/PBRsphere/grey.png");
	//rend1->rendererInitPBR("../shader/PBRshader.txt", "../samples/PBRsphere/pbrSphere.obj", "../samples/PBRsphere/basecolor.png", "../samples/PBRsphere/basecolor.png", "../samples/PBRsphere/normal.png", "../samples/PBRsphere/metallic.png", "../samples/PBRsphere/roughness.png", "../samples/PBRsphere/grey.png");
	rend1->rendererInit("../shader/shader.txt", "../samples/Mono_Lake_C/cube.obj", "../samples/Mono_Lake_C/Mono_Lake_C_Ref.hdr");
	//rend->rendererInitPBR("../shader/PBRshader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");



	//std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();
	//sound->audioSourceInit("../sounds/dixie_horn.ogg");
	//sound->playAudio();
	engine->start();
	std::cout << "Update Finished" << std::endl;
	return 0;
}

