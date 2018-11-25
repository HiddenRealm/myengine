#include "Core.h"
#include "Entity.h"
#include "iostream"

#include "Sound.h"
#include "Input.h"
#include "Move.h"
#include "MeshRenderer.h"

#include <GL/glew.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace myengine
{

std::shared_ptr<Core> Core::initialize()
{
  std::shared_ptr<Core> setup = std::make_shared<Core>();
  setup->running = false;
  setup->self = setup;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
	  std::cout << "SDL Failed to Init" << std::endl;
  }

  setup->window = SDL_CreateWindow("My Engine",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (!SDL_GL_CreateContext(setup->window))
  {
	  std::cout << "Failed create a context with window" << std::endl;
  }

  if(glewInit() != GLEW_OK)
  {
	  std::cout << "GLEW Failed to Init" << std::endl;
  }

  setup->device = alcOpenDevice(NULL);

  if (!setup->device)
  {
	  std::cout << "OpenAL Failed to Init" << std::endl;
  }

  setup->context = alcCreateContext(setup->device, NULL);

  if (!setup->context)
  {
	  alcCloseDevice(setup->device);
	  std::cout << "OpenAL Failed to Init" << std::endl;
  }

  if (!alcMakeContextCurrent(setup->context))
  {
	  alcDestroyContext(setup->context);
	  alcCloseDevice(setup->device);
	  std::cout << "OpenAL Failed to Init" << std::endl;
  }

  return setup;
}

void Core::start()
{
  running = true;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  while(running)
  {
	SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
	  if(event.type == SDL_QUIT)
      {
        running = false;
      }
    }

    for(std::vector<std::shared_ptr<Entity>>::iterator count = entities.begin(); count != entities.end(); count++)
    {
      (*count)->update();
    }

	playAudio();
	movement();
	randMove();

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<std::shared_ptr<Entity> >::iterator count = entities.begin();
		count != entities.end(); count++)
	{
		(*count)->display();
	}

    SDL_GL_SwapWindow(window);
  }
}

void Core::stop()
{
  running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
  std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
  entities.push_back(rtn);
  rtn->self = rtn;
  rtn->core = self;

  return rtn;
}

void Core::playAudio()
{
	for (std::vector<std::shared_ptr<Entity>>::iterator count = entities.begin(); count != entities.end(); count++)
	{
		if ((*count)->checkComponent<myengine::Sound>() && (*count)->checkComponent<myengine::Input>())
		{
			std::shared_ptr<myengine::Input> input = (*count)->getComponent<myengine::Input>();
			std::shared_ptr<myengine::Sound> audio = (*count)->getComponent<myengine::Sound>();

			if (input->checkSpace())
			{
				if (audio->isPlaying() == false)
				{
					audio->play();
					std::cout << "Space" << std::endl;
				}
			}
		}
	}
}

void Core::movement()
{
	for (std::vector<std::shared_ptr<Entity>>::iterator count = entities.begin(); count != entities.end(); count++)
	{
		if ((*count)->checkComponent<myengine::MeshRenderer>() && (*count)->checkComponent<myengine::Input>())
		{
			std::shared_ptr<myengine::Input> input = (*count)->getComponent<myengine::Input>();
			std::shared_ptr<myengine::MeshRenderer> skin = (*count)->getComponent<myengine::MeshRenderer>();

			glm::vec3 pos;

			if (input->checkW())
			{
				pos = { 0, 0, -0.25 };
				skin->setPos(pos);
			}
			if (input->checkA())
			{
				pos = { -0.25, 0, 0 };
				skin->setPos(pos);
			}
			if (input->checkS())
			{
				pos = { 0, 0, 0.25 };
				skin->setPos(pos);
			}
			if (input->checkD())
			{
				pos = { 0.25, 0, 0 };
				skin->setPos(pos);
			}
		}
	}
}

void Core::randMove()
{
	for (std::vector<std::shared_ptr<Entity>>::iterator count = entities.begin(); count != entities.end(); count++)
	{
		if ((*count)->checkComponent<myengine::MeshRenderer>() && (*count)->checkComponent<myengine::Move>())
		{
			std::shared_ptr<myengine::MeshRenderer> skin = (*count)->getComponent<myengine::MeshRenderer>();
			std::shared_ptr<myengine::Move> move = (*count)->getComponent<myengine::Move>();

			glm::vec3 pos;

			if (move->getPos() == 1)
			{
				pos = { 0, 0, -0.15 };
			}
			if (move->getPos() == 2)
			{
				pos = { -0.15, 0, 0 };
			}
			if (move->getPos() == 3)
			{
				pos = { 0, 0, 0.15 };
			}
			if (move->getPos() == 4)
			{
				pos = { 0.15, 0, 0 };
			}
			skin->setPos(pos);
		}
	}
}

}
