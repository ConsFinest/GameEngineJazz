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
	std::shared_ptr<Transform> trans = camEnt->addComponent<Transform>();
	std::shared_ptr<Camera> cam = camEnt->addComponent<Camera>();
	trans->setPos(glm::vec3(0, 0, 5));
	cam->cameraInit(60);
	

	std::shared_ptr<Transform> transform = entity->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	
	std::shared_ptr<Renderer> rend = entity->addComponent<Renderer>();
	rend->setCamera(cam);
	//rend->rendererInit("../shader/Shader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");
	rend->rendererInitPBR("../shader/PBRshader.txt", "../samples/PBRsphere/pbrSphere.obj", "../samples/PBRsphere/grey.png","../samples/PBRsphere/basecolor.png", "../samples/PBRsphere/normal.png", "../samples/PBRsphere/metallic.png", "../samples/PBRsphere/roughness.png", "../samples/PBRsphere/grey.png");
	//rend->rendererInitPBR("../shader/PBRshader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");



	//std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();
	//sound->audioSourceInit("../sounds/dixie_horn.ogg");
	//sound->playAudio();
	engine->start();
	std::cout << "Update Finished" << std::endl;
	return 0;
}

