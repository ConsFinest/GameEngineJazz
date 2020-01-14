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
#include <GameEngine/skyBox.h>
#include <memory>


int main()
{
	std::shared_ptr<Engine> engine = Engine::intialize();

	std::shared_ptr<Entity> GuiEnt = engine->addEntity();
	std::shared_ptr<GUI> gui = GuiEnt->addComponent<GUI>();
	gui->GUIInit("../shader/GUIshader.txt", { 150,150,1 }, "../samples/crosshair.png", { WINDOW_WIDTH/2-75,WINDOW_HEIGHT/2-75 });



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
	cam2->playerControll(true);
	cam2->cameraInit(60);

	std::shared_ptr<Entity> skyBox = engine->addEntity();
	std::shared_ptr<Transform> transform1 = skyBox->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Renderer> skyRend = skyBox->addComponent<Renderer>();
	std::shared_ptr<Skybox> sky = skyBox->addComponent<Skybox>();

	skyBox->setSkyBox(true);
	skyRend->rendererInit("../shader/shader.txt", "../samples/PBRsphere/Skybox.obj", "../samples/PBRsphere/Mono_Lake_C_HiRes.jpg");

	std::shared_ptr<Entity> player = engine->addEntity();
	std::shared_ptr<Transform> pTrans = player->addComponent<Transform>(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	std::shared_ptr<Renderer> pRend = player->addComponent<Renderer>();

	pRend->rendererInit("../shader/shader.txt", "../samples/PBRsphere/pbrSphere.obj", "../samples/PBRsphere/basecolor.png");


	//Building level with cubes
	//floor 
	std::shared_ptr<Entity> cube1 = engine->addEntity();
	std::shared_ptr<Transform> transformC1 = cube1->addComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 1, 10));
	std::shared_ptr<boxCollider> cube1BC = cube1->addComponent<boxCollider>();
	cube1BC->onInit({ 10,1,10 }, false);
	std::shared_ptr<Renderer> cube1R = cube1->addComponent<Renderer>();
	cube1R->rendererInit("../shader/shader.txt", "../samples/cube.obj", "../samples/white.png");

	//WallBack
	std::shared_ptr<Entity> cube2 = engine->addEntity();
	std::shared_ptr<Transform> transformC2 = cube2->addComponent<Transform>(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(10, 10, 1));
	std::shared_ptr<boxCollider> cube2BC = cube2->addComponent<boxCollider>();
	cube2BC->onInit({ 10,10,1 }, false);
	std::shared_ptr<Renderer> cube2R = cube2->addComponent<Renderer>();
	cube2R->rendererInit("../shader/shader.txt", "../samples/cube.obj", "../samples/white.png");

	//wallRight
	std::shared_ptr<Entity> cube3 = engine->addEntity();
	std::shared_ptr<Transform> transformC3 = cube3->addComponent<Transform>(glm::vec3(10, 10, 0), glm::vec3(0, 0, 0), glm::vec3(1, 10, 10));
	std::shared_ptr<boxCollider> cube3BC = cube3->addComponent<boxCollider>();
	cube3BC->onInit({ 1,10,10 }, false);
	std::shared_ptr<Renderer> cube3R = cube3->addComponent<Renderer>();
	cube3R->rendererInit("../shader/shader.txt", "../samples/cube.obj", "../samples/white.png");

	//wallLeft
	std::shared_ptr<Entity> cube4 = engine->addEntity();
	std::shared_ptr<Transform> transformC4 = cube4->addComponent<Transform>(glm::vec3(-10, 10, 0), glm::vec3(0, 0, 0), glm::vec3(1, 10, 10));
	std::shared_ptr<boxCollider> cube4BC = cube4->addComponent<boxCollider>();
	cube4BC->onInit({ 1,10,10 }, false);
	std::shared_ptr<Renderer> cube4R = cube4->addComponent<Renderer>();
	cube4R->rendererInit("../shader/shader.txt", "../samples/cube.obj", "../samples/white.png");

	//WallFront
	std::shared_ptr<Entity> cube5 = engine->addEntity();
	std::shared_ptr<Transform> transformC5 = cube5->addComponent<Transform>(glm::vec3(0, 10, 10), glm::vec3(0, 0, 0), glm::vec3(10, 10, 1));
	std::shared_ptr<boxCollider> cube5BC = cube5->addComponent<boxCollider>();
	cube5BC->onInit({ 10,10,1 }, false);
	std::shared_ptr<Renderer> cube5R = cube5->addComponent<Renderer>();
	cube5R->rendererInit("../shader/shader.txt", "../samples/cube.obj", "../samples/white.png");

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