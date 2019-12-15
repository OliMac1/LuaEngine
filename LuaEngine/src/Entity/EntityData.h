#pragma once

#include <unordered_map>
#include <sol/sol.hpp>
#include "Entity.h"

class Entity;
class EntityData
{
	std::unordered_map<std::string, std::pair<unsigned int, std::pair<sol::object (*)( const Entity*, unsigned int, sol::state_view& ), void( * )( Entity*, unsigned int, sol::stack_object& )>>> data;
  std::vector<unsigned int> componentOffsets;

public:
  template <class type>
	void add_mapping (std::string& name, unsigned int offset);
	void set (std::string& name, Entity* block, sol::stack_object& value);
	sol::object get (std::string& name, Entity* block, sol::state_view state);
	size_t length ()
	{
		return data.size ();
	}
  std::vector<unsigned int>& getComponentOffsets();
};

template <class type>
void EntityData::add_mapping(std::string& name, unsigned int offset)
{
  data[name] = std::pair(offset, std::pair(&Entity::get<type>, &Entity::set<type>));
}

template<> 
void EntityData::add_mapping<Component>(std::string& name, unsigned int offset);
