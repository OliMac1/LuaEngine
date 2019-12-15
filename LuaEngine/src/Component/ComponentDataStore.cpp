#include "ComponentDataStore.h"

sol::object ComponentDataStore::get(unsigned int id, std::string& key, Component* c, sol::state_view view)
{
  return dataStore.at(id).get(key, c, view);
}

void ComponentDataStore::set(unsigned int id, std::string& key, Component* c, sol::stack_object& value)
{
  dataStore.at(id).set(key, c, value);
}

size_t ComponentDataStore::length(unsigned int id)
{
  return dataStore.at(id).length();
}

void ComponentDataStore::resize(unsigned int size)
{
  dataStore.resize(size);
}
