#include "EntityDataStore.h"

void EntityDataStore::resize (size_t capacity)
{
  store.resize(capacity);
}

size_t EntityDataStore::length (size_t id)
{
	return store.at (id).length ();
}

void EntityDataStore::set (size_t id, std::string& name, Entity* block, sol::stack_object& value)
{
	store.at (id).set (name, block, value);
}

sol::object EntityDataStore::get (size_t id, std::string& name, Entity* block, sol::state_view state)
{
	return store.at (id).get (name, block, state);
}

std::vector<unsigned int>& EntityDataStore::getComponentOffsets(size_t id)
{
  return store.at(id).getComponentOffsets();
}
