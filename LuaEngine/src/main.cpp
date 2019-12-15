#include <iostream>
#include <sol/sol.hpp>
#include <Management/Game.h>

static sol::object init_component(unsigned int componentId, sol::this_state ts)
{
  return sol::make_object(ts, std::move(Game::componentFactory.generateComponent(componentId)));
}

int main()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base);

  lua.set_function("init_component", &init_component);

  lua.script_file("lua/script.lua");
  lua.script_file("lua/second.lua");

  lua.new_usertype<Entity>("Entity",
    sol::meta_function::index, &Entity::dynamic_get,
    sol::meta_function::new_index, &Entity::dynamic_set,
    sol::meta_function::length, &Entity::dynamic_length
    );

  lua.new_usertype<Component>("Component",
    sol::meta_function::index, &Component::dynamic_get,
    sol::meta_function::new_index, &Component::dynamic_set,
    sol::meta_function::length, &Component::dynamic_length
    );

  {
    Game::entityDataStore.resize(4);
    Game::entityFactory.addMapping(0, 16);
    Game::entityFactory.addMapping(1, 8);
    Game::entityFactory.addMapping(2, 16);
    Game::entityFactory.addMapping(3, 16);
    Game::componentDataStore.resize(1);
    Game::componentFactory.addMapping(0, 16);

    std::string refName = "number";
    Game::entityDataStore.add_mapping<double>(0, refName, 0);
    refName = "number2";
    Game::entityDataStore.add_mapping<long long>(0, refName, 8);

    refName = "a";
    Game::entityDataStore.add_mapping<int>(1, refName, 0);
    refName = "b";
    Game::entityDataStore.add_mapping<int>(1, refName, 4);

    refName = "a";
    Game::entityDataStore.add_mapping<sol::function>(2, refName, 0);

    refName = "a";
    Game::entityDataStore.add_mapping<Component>(3, refName, 0);

    refName = "a";
    Game::componentDataStore.add_mapping<double>(0, refName, 0);
    refName = "b";
    Game::componentDataStore.add_mapping<long long>(0, refName, 8);

    sol::function func = lua["entity"]["BaseGame"]["crafter"]["update"];
    Game::entityCallbacks.addUpdate(0, func);
    func = lua["entity"]["BaseGame"]["crafter"]["onCreate"];
    Game::entityCallbacks.addOnCreate(0, func);
    func = lua["entity"]["BaseGame"]["fibonacci"]["update"];
    Game::entityCallbacks.addUpdate(1, func);
    func = lua["entity"]["BaseGame"]["fibonacci"]["onCreate"];
    Game::entityCallbacks.addOnCreate(1, func);
    func = lua["entity"]["BaseGame"]["functionTest"]["onCreate"];
    Game::entityCallbacks.addOnCreate(2, func);
    func = lua["entity"]["BaseGame"]["functionTest"]["update"];
    Game::entityCallbacks.addUpdate(2, func);
    func = lua["entity"]["BaseGame"]["componentTest"]["onCreate"];
    Game::entityCallbacks.addOnCreate(3, func);
    func = lua["entity"]["BaseGame"]["componentTest"]["update"];
    Game::entityCallbacks.addUpdate(3, func);

    std::vector<Entity> entities;
    //for (int i = 0; i < 100; ++i)
    //{
    //  entities.push_back(bf.generateEntity(2, &bds));
    //}
    entities.push_back(Game::entityFactory.generateEntity(0));
    entities.push_back(Game::entityFactory.generateEntity(3));

    for (Entity& e : entities)
    {
      e.onCreate();
      e.onStart();
      e.onResume();
    }


    //b2.update(bc);
    for (int i = 0; i < 10; ++i)
    {
      for (Entity& e : entities)
      {
        e.update();
      }
    }

    for (Entity& e : entities)
    {
      e.onPause();
      e.onStop();
      e.onDestroy();
    }

    std::cout << "normal operation complete!\n";
  }
}