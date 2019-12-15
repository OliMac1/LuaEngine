#pragma once

class ComponentDataStore;

#include <sol/sol.hpp>
#include "Component.h"
#include "ComponentData.h"

class ComponentDataStore
{
  std::vector<ComponentData> dataStore;
public:
  sol::object get(unsigned int id, std::string& key, Component* c, sol::state_view view);

  template<class type>
  void add_mapping(size_t id, std::string& name, unsigned int offset);
  void set(unsigned int id, std::string& key, Component* c, sol::stack_object& value);
  size_t length(unsigned int id);
  void resize(unsigned int size);
};

template<class type>
void ComponentDataStore::add_mapping(size_t id, std::string& name, unsigned int offset)
{
  dataStore.at(id).add_mapping(name, offset, &Component::get<type>, &Component::set<type>);
}