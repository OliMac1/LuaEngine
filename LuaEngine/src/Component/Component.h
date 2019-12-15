#pragma once

class Component;

#include "ComponentDataStore.h"
#include <sol/sol.hpp>

class Component
{
  friend class ComponentFactory;
  friend class Entity;

  unsigned int id, size;
  void* data; // owned data

  void* memloc(unsigned int x) const
  {
    return ( char*) data + x;
  }

  Component(unsigned int id, unsigned int size);
  void makeValid()
  {
    data = nullptr;
  }
  void clearUp()
  {
    operator delete( data );
    data = nullptr;
  }

public:
  Component(const Component& other);
  Component operator=(const Component& other);
  Component(Component&& other);
  Component operator=(Component&& other);
  ~Component();

  sol::object dynamic_get(std::string key, sol::this_state ts);
  void dynamic_set(std::string key, sol::stack_object so);
  size_t dynamic_length();

  template<class type>
  static void set(Component* block, unsigned int, sol::stack_object& x);

  template<class type>
  static sol::object get(Component const* block, unsigned int, sol::state_view& thisState);
};

template<class type>
inline void Component::set(Component* block, unsigned int offset, sol::stack_object& x)
{
  type* mem = static_cast<type*>( block->memloc(offset) );
  *mem = std::move( x.as<type>() );
}

template<class type>
inline sol::object Component::get(Component const* block, unsigned int offset, sol::state_view& thisState)
{
  type* mem = static_cast<type*>( block->memloc(offset) );
  return sol::make_object(thisState, *mem);
}