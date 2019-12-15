#include "ComponentData.h"

void ComponentData::add_mapping(std::string& name, unsigned int offset, sol::object(*getter)( const Component*, unsigned int, sol::state_view& ), void( *setter )( Component*, unsigned int, sol::stack_object& ))
{
  data[name] = std::pair(offset, std::pair(getter, setter));
}

void ComponentData::set(std::string& name, Component* component, sol::stack_object& value)
{
  auto mapping = data.at(name);
  mapping.second.second(component, mapping.first, value);
}

sol::object ComponentData::get(std::string& name, Component* component, sol::state_view state)
{
  auto mapping = data.at(name);
  return mapping.second.first(component, mapping.first, state);
}
