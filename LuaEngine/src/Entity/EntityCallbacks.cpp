#include "EntityCallbacks.h"

void EntityCallbacks::addOnCreate(unsigned int id, sol::function& func) {
		callbacks[id][ON_CREATE] = func;
}
void EntityCallbacks::addOnDestroy(unsigned int id, sol::function& func) {
	callbacks[id][ON_DESTROY] = func;
}
void EntityCallbacks::addOnStart(unsigned int id, sol::function& func) {
	callbacks[id][ON_START] = func;
}
void EntityCallbacks::addOnStop(unsigned int id, sol::function& func) {
	callbacks[id][ON_STOP] = func;
}
void EntityCallbacks::addOnPause(unsigned int id, sol::function& func) {
	callbacks[id][ON_PAUSE] = func;
}
void EntityCallbacks::addOnResume(unsigned int id, sol::function& func) {
	callbacks[id][ON_RESUME] = func;
}
void EntityCallbacks::addUpdate(unsigned int id, sol::function& func) {
	callbacks[id][UPDATE] = func;
}