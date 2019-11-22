cmake_minimum_required(VERSION 2.6)
project(ENGINEJAZZ)

include_directories(src contrib)

#add_definitions(-DSTD_SR1_DEBUG)

add_library(rend
  	src/rend/Exception.cpp
  	src/rend/Context.cpp
  	src/rend/Texture.cpp
  	src/rend/RenderTexture.cpp
  	src/rend/Shader.cpp
  	src/rend/Buffer.cpp
  	src/rend/Mesh.cpp
  	src/rend/Util.cpp
)
if(MSVC)
  target_link_libraries(rend glew32 opengl32 OpenAl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_library(GameEngine
	src/GameEngine/engine.cpp
	src/GameEngine/engine.h
	src/GameEngine/entity.cpp
	src/GameEngine/entity.h
	src/GameEngine/component.cpp
	src/GameEngine/component.h
	src/GameEngine/renderer.h
	src/GameEngine/renderer.cpp
	src/GameEngine/transform.cpp
	src/GameEngine/transform.h
	src/GameEngine/camera.cpp
	src/GameEngine/camera.h
	src/GameEngine/audioSource.h
	src/GameEngine/audioSource.cpp

)
target_link_libraries(GameEngine SDL2 rend OpenAl32)

add_executable(Game
	src/Game/main.cpp
)
target_link_libraries(Game GameEngine)