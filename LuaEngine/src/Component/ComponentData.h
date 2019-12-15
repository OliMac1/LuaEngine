#pragma once

class ComponentData;

#include "Component.h"

class ComponentData
{
  std::unordered_map<std::string, std::pair<unsigned int, std::pair<sol::object(*)( const Component*, unsigned int, sol::state_view& ), void( * )( Component*, unsigned int, sol::stack_object& )>>> data;

public:
  void add_mapping(std::string& name, unsigned int offset, sol::object(*getter)( const Component*, unsigned int, sol::state_view& ), void( *setter )( Component*, unsigned int, sol::stack_object& ));
  void set(std::string& name, Component* block, sol::stack_object& value);
  sol::object get(std::string& name, Component* block, sol::state_view state);
  size_t length()
  {
    return data.size();
  }
};