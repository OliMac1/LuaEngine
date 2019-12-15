#pragma once
#include <sol/sol.hpp>
#include <unordered_map>

constexpr unsigned int ON_CREATE = 0;
constexpr unsigned int ON_DESTROY = 1;
constexpr unsigned int ON_START = 2;
constexpr unsigned int ON_STOP = 3;
constexpr unsigned int ON_PAUSE = 4;
constexpr unsigned int ON_RESUME = 5;
constexpr unsigned int UPDATE = 6;

//struct Refs{
//	sol::function onCreate;
//	sol::function onDestroy;
//	sol::function onStart;
//	sol::function onStop;
//	sol::function onPause;
//	sol::function onResume;
//	sol::function update;
//	Refs(lua_State* L) : onCreate(L), onDestroy(L), onStart(L), onStop(L), onPause(L), onResume(L), update(L) {}
//};

class EntityCallbacks {
	std::unordered_map<unsigned int, std::array<sol::function,7>> callbacks;
public:
	//BlockCallbacks(lua_State *L) : L(L){}

	void addOnCreate(unsigned int id, sol::function& func);
	void addOnDestroy(unsigned int id, sol::function& func);
	void addOnStart(unsigned int id, sol::function& func);
	void addOnStop(unsigned int id, sol::function& func);
	void addOnPause(unsigned int id, sol::function& func);
	void addOnResume(unsigned int id, sol::function& func);
	void addUpdate(unsigned int id, sol::function& func);


	sol::function& onCreate(unsigned int id) {
		return callbacks.at(id)[ON_CREATE];
	}
	sol::function& onDestroy(unsigned int id) {
		return callbacks.at(id)[ON_DESTROY];
	}
	sol::function& onStart(unsigned int id) {
		return callbacks.at(id)[ON_START];
	}
	sol::function& onStop(unsigned int id) {
		return callbacks.at(id)[ON_STOP];
	}
	sol::function& onPause(unsigned int id) {
		return callbacks.at(id)[ON_PAUSE];
	}
	sol::function& onResume(unsigned int id) {
		return callbacks.at(id)[ON_RESUME];
	}
	sol::function& update(unsigned int id) {
		return callbacks.at(id)[UPDATE];
	}
};