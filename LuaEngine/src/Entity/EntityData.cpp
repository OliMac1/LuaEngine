#include "EntityData.h"

void EntityData::set (std::string& name, Entity* block, sol::stack_object& value)
{
	try
	{
		auto element = data.at (name);
		if (element.second.second == nullptr)
		{
			throw std::exception (": read only");
		}
		element.second.second (block, element.first, value);
	}
	catch (std::exception& e)
	{
		throw std::out_of_range ("Failed to access " + name + e.what ());
	}
}

sol::object EntityData::get (std::string& name, Entity* block, sol::state_view state)
{
	try
	{
		auto element = data.at (name);
		return element.second.first (block, element.first, state);
	}
	catch (std::exception& e)
	{
		throw std::out_of_range ("Failed to access " + name + e.what ());
	}
}

std::vector<unsigned int>& EntityData::getComponentOffsets()
{
  return componentOffsets;
}

template <>
void EntityData::add_mapping<Component>(std::string& name, unsigned int offset)
{
  componentOffsets.push_back(offset);
  data[name] = std::pair(offset, std::pair(&Entity::get<Component>, &Entity::set<Component>));
}


