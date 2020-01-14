#include <iostream>

#define STB_IMAGE_IMPLEMENTATION



#include <GameEngine/engine.h>
#include <GameEngine/component.h>
#include <GameEngine/entity.h>
#include <GameEngine/renderer.h>

#include <GameEngine/transform.h>
#include <GameEngine/camera.h>
#include <GameEngine/boxCollider.h>
#include <GameEngine/GUI.h>

#include <memory>


int main()
{
	std::shared_ptr<Engine> engine = Engine::intialize();

	std::shared_ptr<Entity> entity = engine->addEntity();
	std::shared_ptr<Transform> transform = entity->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Renderer> rend = entity->addComponent<Renderer>();
	std::shared_ptr<boxCollider> boxColEnt = entity->addComponent<boxCollider>();
	boxColEnt->setSize({ 1,1,1 });
	boxColEnt->setMoveable(false);

	std::shared_ptr<Entity> GuiEnt = engine->addEntity();
	std::shared_ptr<GUI> gui = GuiEnt->addComponent<GUI>();


	std::shared_ptr<Entity> camEnt = engine->addEntity();
	std::shared_ptr<Transform> trans = camEnt->addComponent<Transform>();
	trans->setPos(glm::vec3(0, 0, 5));
	std::shared_ptr<boxCollider> boxCol = camEnt->addComponent<boxCollider>();
	boxCol->setMoveable(true);
	boxCol->setSize({ 1,1,1 });
	std::shared_ptr<Camera> cam = camEnt->addComponent<Camera>();
	cam->setCurrent();
	cam->playerControll(true);
	cam->cameraInit(60);

	std::shared_ptr<Entity> camEnt2 = engine->addEntity();
	std::shared_ptr<Transform> trans2 = camEnt2->addComponent<Transform>();
	trans2->setPos(glm::vec3(0, 10, 5));
	std::shared_ptr<boxCollider> boxCol2 = camEnt2->addComponent<boxCollider>();
	
	boxCol2->setSize({ 1,1,1 });
	std::shared_ptr<Camera> cam2 = camEnt2->addComponent<Camera>();
	//cam2->setCurrent();
	cam2->playerControll(true);
	cam2->cameraInit(60);

	std::shared_ptr<Entity> skyBox = engine->addEntity();
	std::shared_ptr<Transform> transform1 = skyBox->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Renderer> skyRend = skyBox->addComponent<Renderer>();
	skyBox->setSkyBox(true);

	std::shared_ptr<Entity> player = engine->addEntity();
	std::shared_ptr<Transform> pTrans = player->addComponent<Transform>(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Renderer> pRend = player->addComponent<Renderer>();

	

	

	rend->rendererInit("../shader/shader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");
	skyRend->rendererInit("../shader/shader.txt", "../samples/PBRsphere/Skybox.obj", "../samples/PBRsphere/Mono_Lake_C_HiRes.jpg");
	pRend->rendererInit("../shader/shader.txt", "../samples/PBRsphere/pbrSphere.obj", "../samples/PBRsphere/basecolor.png");
	gui->GUIInit("../shader/GUIshader.txt", { 200,100,1 }, "../samples/PBRsphere/reticle.png", { 50,50 });

	//std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();
	//sound->audioSourceInit("../sounds/dixie_horn.ogg");
	//sound->playAudio();
	engine->start();
	std::cout << "Update Finished" << std::endl;
	return 0;
}

//TODO add static mesh Collider
//TODO stop being able to push colliders around
//TODO fix cameras being in same pos lmaoin playercontroller