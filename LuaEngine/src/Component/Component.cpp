#include "Component.h"
#include <Management/Game.h>

Component::Component(unsigned int id, unsigned int size) : id(id), size(size), data(operator new( size ))
{
  if (data == nullptr)
  {
    throw std::exception("component memory allocation failed!");
  }
}

Component::Component(const Component& other) : Component(other.id, other.size)
{
  memcpy(data, other.data, size);
}

Component Component::operator=(const Component& other)
{
  if (this != &other)
  {
    id = other.id;
    size = other.size;

    delete data;
    data = operator new( size );
    memcpy(data, other.data, size);
  }
  return *this;
}

Component::Component(Component&& other) : Component(other.id, other.size)
{
  //transfer data ownership
  data = other.data;

  //relinquish data ownership
  other.data = nullptr;
}

Component Component::operator=(Component&& other)
{
  if (this != &other)
  {
    operator delete( data );
    id = other.id;
    size = other.size;

    data = operator new( size );
    data = other.data;

    //relinquish ownership
    other.data = nullptr;
  }
  return *this;
}

Component::~Component()
{
  operator delete( data );
}

sol::object Component::dynamic_get(std::string key, sol::this_state ts)
{
  return Game::componentDataStore.get(id, key, this, ts);
}

void Component::dynamic_set(std::string key, sol::stack_object so)
{
  Game::componentDataStore.set(id, key, this, so);
}

size_t Component::dynamic_length()
{
  return Game::componentDataStore.length(id);
}
