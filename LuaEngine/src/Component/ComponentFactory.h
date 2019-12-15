#pragma once

class ComponentFactory;

#include "Component.h"
#include "ComponentDataStore.h"
#include <unordered_map>

class ComponentFactory
{
private:
  //ids -> size
  std::unordered_map<unsigned int, unsigned int> sizeMap;
  //generate Block with correct id and data unit size
public:
  Component generateComponent(unsigned int id)
  {
    return Component(id, sizeMap.at(id));
  }

  void addMapping(unsigned int id, unsigned int size)
  {
    sizeMap[id] = size;
  }

};
