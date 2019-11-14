cmake_minimum_required(VERSION 2.6)
project(ENGINEJAZZ)

include_directories(src contrib)

add_definitions(-DSTD_SR1_DEBUG)

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
  	src/GameEngine/Context.cpp
  	src/GameEngine/Texture.cpp
  	src/GameEngine/RenderTexture.cpp
  	src/GameEngine/Shader.cpp
  	src/GameEngine/Buffer.cpp
	src/GameEngine/Context.h
  	src/GameEngine/Texture.h
  	src/GameEngine/RenderTexture.h
  	src/GameEngine/Shader.h
  	src/GameEngine/Buffer.h

)
target_link_libraries(GameEngine SDL2 opengl32 glew32)

add_executable(Game
	src/Game/main.cpp
)
target_link_libraries(Game GameEngine)