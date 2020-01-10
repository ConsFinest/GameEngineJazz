#include <iostream>

#define STB_IMAGE_IMPLEMENTATION


#include <GameEngine/engine.h>
#include <GameEngine/component.h>
#include <GameEngine/entity.h>
#include <GameEngine/renderer.h>

#include <GameEngine/transform.h>
#include <GameEngine/camera.h>

#include <memory>


int main()
{

	std::shared_ptr<Engine> engine = Engine::intialize();
	std::shared_ptr<Entity> entity = engine->addEntity();
	std::shared_ptr<Entity> camEnt = engine->addEntity();



	std::shared_ptr<Entity> skyBox = engine->addEntity();
	std::shared_ptr<Transform> trans = camEnt->addComponent<Transform>();

	trans->setPos(glm::vec3(0, 0, 5));
	

	
	std::shared_ptr<Transform> transform = entity->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Transform> transform1 = skyBox->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));

	std::shared_ptr<Camera> cam = camEnt->addComponent<Camera>();

	cam->cameraInit(60);

	std::shared_ptr<Renderer> skyRend = skyBox->addComponent<Renderer>();

	
	
	skyRend->rendererInit("../shader/shader.txt", "../samples/PBRsphere/Skybox.obj", "../samples/PBRsphere/Mono_Lake_C_HiRes.jpg");
	
	//std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();
	//sound->audioSourceInit("../sounds/dixie_horn.ogg");
	//sound->playAudio();
	engine->start();
	std::cout << "Update Finished" << std::endl;
	return 0;
}

