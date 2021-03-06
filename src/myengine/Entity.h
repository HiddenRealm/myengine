#include "Component.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

namespace myengine
{

class Core;

class Entity
{
  friend class Core;

public:

  template <typename T>
  std::shared_ptr<T> addComponent()
  {
	std::shared_ptr<T> rtn = std::make_shared<T>();
	rtn->entity = self;
	rtn->began = false;
	components.push_back(rtn);
    rtn->initialize();

    return rtn;
  }

  template <typename T, typename A>
  std::shared_ptr<T> addComponent(A a)
  {
	  std::shared_ptr<T> rtn = std::make_shared<T>();
	  rtn->entity = self;
	  rtn->began = false;
	  components.push_back(rtn);
	  rtn->initialize(a);

	  return rtn;
  }

  template <typename T, typename A, typename B>
  std::shared_ptr<T> addComponent(A a, B b)
  {
	  std::shared_ptr<T> rtn = std::make_shared<T>();
	  rtn->entity = self;
	  rtn->began = false;
	  components.push_back(rtn);
	  rtn->initialize(a, b);

	  return rtn;
  }

  template <typename T, typename A, typename B, typename C>
  std::shared_ptr<T> addComponent(A a, B b, C c)
  {
	  std::shared_ptr<T> rtn = std::make_shared<T>();
	  rtn->entity = self;
	  rtn->began = false;
	  components.push_back(rtn);
	  rtn->initialize(a, b, c);

	  return rtn;
  }

  template <typename T>
  std::shared_ptr<T> getComponent()
  {
	  for (size_t i = 0; i < components.size(); i++)
	  {
		  std::shared_ptr<T> list = std::dynamic_pointer_cast<T>(components.at(i));

		  if (list)
		  {
			  return list;
		  }
	  }
  }

  template <typename T>
  bool checkComponent()
  {
	  for (size_t i = 0; i < components.size(); i++)
	  {
		  if (std::dynamic_pointer_cast<T>(components.at(i)) != NULL)
		  {
			  return true;
		  }
	  }
	  return false;
  }

  std::shared_ptr<Core> getCore();

private:
  std::weak_ptr<Entity> self;
  std::weak_ptr<Core> core;
  std::vector<std::shared_ptr<Component> > components;

  void update();
  void display();
};

}
