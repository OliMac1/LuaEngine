#pragma once

#include <vector>
#include "EntityData.h"

class EntityData;
class Entity;
class EntityDataStore
{
	std::vector<EntityData> store;

public:
	void shrink_to_fit ()
	{
		store.shrink_to_fit ();
	}
	void resize (size_t capacity);
	size_t length (size_t id);
  template <class type>
	void add_mapping (size_t id, std::string& name, unsigned int offset);
	void set (size_t id, std::string& name, Entity* block, sol::stack_object& value);
	sol::object get (size_t id, std::string& name, Entity* block, sol::state_view state);
  std::vector<unsigned int>& getComponentOffsets(size_t id);
};

template <class type>
void EntityDataStore::add_mapping(size_t id, std::string& name, unsigned int offset)
{
  store.at(id).add_mapping<type>(name, offset);
}
