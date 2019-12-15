#pragma once

#include <Entity/Entity.h>
#include <Component/ComponentDataStore.h>
#include <Entity/EntityFactory.h>
#include <Component/ComponentFactory.h>

namespace Game
{
  extern EntityDataStore entityDataStore;
  extern ComponentDataStore componentDataStore;
  extern EntityFactory entityFactory;
  extern ComponentFactory componentFactory;
  extern EntityCallbacks entityCallbacks;
};