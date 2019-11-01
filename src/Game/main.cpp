#include <iostream>

#include <GameEngine/engine.h>
#include <GameEngine/component.h>
#include <GameEngine/entity.h>
#include <GameEngine/triangleRenderer.h>
#include <memory>

int main()
{

	std::shared_ptr<Engine> engine = Engine::intialize();
	std::cout << "ENGINE JAZZ HELLO" << std::endl;
	
	std::shared_ptr<Entity> entity = engine->addEntity();

	std::shared_ptr<Triangle> tri = entity->addComponent<Triangle>();
	
	engine->start();
 	std::cout << "Update Finished" << std::endl;
	
	return 0;
}