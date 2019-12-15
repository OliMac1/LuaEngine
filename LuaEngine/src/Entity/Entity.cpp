#include "Entity.h"
#include <Management/Game.h>

Entity::Entity(unsigned int id, unsigned int size, bool) : id(id), size(size)
{
}
  
Entity::Entity(unsigned int id, unsigned int size) : Entity(id, size, true)
{
  data = operator new( size );
  if (data == nullptr)
  {
    throw std::exception("failed to allocate memory");
  }
  std::vector<unsigned int>& offsets = Game::entityDataStore.getComponentOffsets(id);
  for (unsigned int offset :offsets)
  {
    Component* comp = static_cast<Component*>( this->memloc(offset) );
    comp->makeValid();
  }
}

Entity::Entity(Entity&& other) : Entity(other.id, other.size, true)
{
  //transfer ownership of pointers
  data = other.data;

  //other relinquish ownership
  other.data = nullptr;
}

Entity& Entity::operator=(Entity&& other)
{
  if (this != &other)
  {
    operator delete( data );

    //transfer ownership
    id = other.id;
    size = other.size;

    data = operator new( size );
    data = other.data;

    //other relinquish ownership
    other.data = nullptr;
  }
  return *this;
}

Entity::~Entity()
{
  if (data != nullptr)
  {
    std::vector<unsigned int>& offsets = Game::entityDataStore.getComponentOffsets(id);
    for (unsigned int offset : offsets)
    {
      Component* comp = static_cast<Component*>( this->memloc(offset) );
      comp->clearUp();
    }
    operator delete( data );
  }
}

void Entity::onCreate()
{
  sol::function& f = Game::entityCallbacks.onCreate(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::onDestroy()
{
  sol::function& f = Game::entityCallbacks.onDestroy(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::onStart()
{
  sol::function& f = Game::entityCallbacks.onStart(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::onStop()
{
  sol::function& f = Game::entityCallbacks.onStop(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::onPause()
{
  sol::function& f = Game::entityCallbacks.onPause(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::onResume()
{
  sol::function& f = Game::entityCallbacks.onResume(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::update()
{
  sol::function& f = Game::entityCallbacks.update(id);
  if (f.valid())
  {
    f(this);
  }
}

void Entity::dynamic_set(std::string key, sol::stack_object value)
{
  Game::entityDataStore.set(id, key, this, value);
}

sol::object Entity::dynamic_get(std::string key, sol::this_state state)
{
  return Game::entityDataStore.get(id, key, this, state);
}

sol::object Entity::get(std::string& key, sol::state& state)
{
  return Game::entityDataStore.get(id, key, this, state);
}

size_t Entity::dynamic_length()
{
  return Game::entityDataStore.length(id);
}
