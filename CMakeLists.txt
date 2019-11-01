cmake_minimum_required(VERSION 2.6)
project(ENGINEJAZZ)

include_directories(src)

add_library(GameEngine
	src/GameEngine/engine.cpp
	src/GameEngine/engine.h
	src/GameEngine/entity.cpp
	src/GameEngine/entity.h
	src/GameEngine/component.cpp
	src/GameEngine/component.h
	src/GameEngine/Exception.cpp
	src/GameEngine/Exception.h
	src/GameEngine/triangle.cpp
	src/GameEngine/triangleRenderer.h
	src/GameEngine/triangleRenderer.cpp
	src/GameEngine/transform.cpp
	src/GameEngine/transform.h
	src/GameEngine/camera.cpp
	src/GameEngine/camera.h

)
target_link_libraries(GameEngine SDL2 opengl32 glew32)

add_executable(Game
	src/Game/main.cpp
)
target_link_libraries(Game GameEngine)