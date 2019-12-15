#pragma once
#include "Entity.h"
#include <unordered_map>

class EntityFactory
{
private:
  //ids -> size
  std::unordered_map<unsigned int, unsigned int> sizeMap;
  //generate Block with correct id and data unit size
public:
  Entity generateEntity(unsigned int id)
  {
    return Entity(id, sizeMap.at(id));
  }
  void addMapping(unsigned int id, unsigned int size)
  {
    sizeMap[id] = size;
  }

};
