#pragma once

#include <Component/Component.h>
#include "EntityCallbacks.h"
#include "EntityDataStore.h"
#include <Component/Component.h>

class EntityData;
class EntityDataStore;
class Entity
{
	friend class EntityFactory;

	unsigned int id, size;
	void* data; //owned data

	void* memloc(unsigned int x) const
	{
		return ( char*) data + x;
	}
  Entity(unsigned int id, unsigned int size, bool);
	Entity(unsigned int id, unsigned int size);

public:
  Entity(const Entity& other) = delete;
  Entity& operator=(const Entity& other) = delete;
	Entity(Entity&& other);
	Entity& operator=(Entity&& other);
  ~Entity();

  void onCreate();

  void onDestroy();

  void onStart();

  void onStop();

  void onPause();

  void onResume();

  void update();

	template<class type>
	static void set(Entity* block, unsigned int, sol::stack_object& x);

	template<class type>
	static sol::object get(Entity const* block, unsigned int, sol::state_view& thisState);

	void dynamic_set(std::string key, sol::stack_object value);

	sol::object dynamic_get(std::string key, sol::this_state state);
	sol::object get(std::string& key, sol::state& state);

	size_t dynamic_length();
};

template<class type>
inline void Entity::set(Entity* block, unsigned int offset, sol::stack_object& x)
{
	type* mem = static_cast<type*>( block->memloc(offset) );
	*mem = std::move(x.as<type>());
}

template<class type>
inline sol::object Entity::get(Entity const* block, unsigned int offset, sol::state_view& thisState)
{
	type* mem = static_cast<type*>( block->memloc(offset) );
  return sol::make_object(thisState, *mem);
}

template<>
inline sol::object Entity::get<Component>(Entity const* block, unsigned int offset, sol::state_view& thisState)
{
  Component* mem = static_cast<Component*>( block->memloc(offset) );
  return sol::make_object(thisState, mem);
}
