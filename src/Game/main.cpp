#include <iostream>

#define STB_IMAGE_IMPLEMENTATION


#include <GameEngine/engine.h>
#include <GameEngine/component.h>
#include <GameEngine/entity.h>
#include <GameEngine/renderer.h>
#include <memory>






//const char* src =
//"#ifdef VERTEX                                 \n" \
//"                                              \n" \
//"attribute vec3 a_Position;                    \n" \
//"attribute vec2 a_TexCoord;                    \n" \
//"attribute vec3 a_Normal;                      \n" \
//"                                              \n" \
//"uniform mat4 u_Projection;                    \n" \
//"uniform mat4 u_Model;                         \n" \
//"                                              \n" \
//"varying vec3 v_Normal;                        \n" \
//"varying vec2 v_TexCoord;                      \n" \
//"                                              \n" \
//"void main()                                   \n" \
//"{                                             \n" \
//"  gl_Position = u_Projection *                \n" \
//"    u_Model * vec4(a_Position, 1);            \n" \
//"                                              \n" \
//"  v_Normal = a_Normal;                        \n" \
//"  v_TexCoord = a_TexCoord;                    \n" \
//"}                                             \n" \
//"                                              \n" \
//"#endif                                        \n" \
//"#ifdef FRAGMENT                               \n" \
//"                                              \n" \
//"uniform sampler2D u_Texture;                  \n" \
//"                                              \n" \
//"varying vec3 v_Normal;                        \n" \
//"varying vec2 v_TexCoord;                      \n" \
//"                                              \n" \
//"void main()                                   \n" \
//"{                                             \n" \
//"  gl_FragColor = texture2D(u_Texture, v_TexCoord);      \n" \
//"  if(gl_FragColor.x == 9) gl_FragColor.x = v_Normal.x;  \n" \
//"}                                             \n" \
//"                                              \n" \
//"#endif                                        \n";


int main()
{

	std::shared_ptr<Engine> engine = Engine::intialize();
	std::shared_ptr<Entity> entity = engine->addEntity();
	std::shared_ptr<Renderer> rend = entity->addComponent<Renderer>();
	rend->rendererInit("../shader/shader.txt", "../samples/graveyard/graveyard.obj", "../samples/graveyard/graveyard.png");
	std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();
	sound->audioSourceInit("../sounds/dixie_horn.ogg");
	sound->playAudio();
	engine->start();
	std::cout << "Update Finished" << std::endl;
	return 0;
}