#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>

namespace myengine
{

class Entity;

class Core
{
public:
	//setUp
  static std::shared_ptr<Core> initialize();
  //start & stop the loop
  void start();
  void stop();
  
  //systems
  void coliP();
  void playAudio(); 
  void movement();
  void randMove();
  std::shared_ptr<Entity> addEntity();

  bool win();

  //void removeEntity(std::shared_ptr<myengine::Entity> e);

private:
  bool running;
  std::vector<std::shared_ptr<Entity>> entities;
  std::weak_ptr<Core> self;

  bool winS = true;

  SDL_Window *window;
  ALCdevice* device;
  ALCcontext* context;

};

}
