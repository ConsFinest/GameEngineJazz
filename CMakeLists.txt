cmake_minimum_required(VERSION 2.6)
project(ENGINEJAZZ)

add_library(GameEngine
	src/GameEngine/engine.cpp
)
target_link_libraries(GameEngine SDL2 opengl32 glew32)

add_executable(Game
	src/Game/main.cpp
)
target_link_libraries(Game GameEngine)