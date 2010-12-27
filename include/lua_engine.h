/* Lua engine that uses plain C-style functions to wrap
 * all the Superscene and Scene methods into a single
 * bundle. */

#ifndef LUA_ENGINE_H_
#define LUA_ENGINE_H_

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "../include/main.h"
#include "../include/superscene.h"

/* Superscene class, handles the actual world */
static Superscene * superscene;

class LuaEngine {
private:
	lua_State *L;
	
public:
	/* Sets Lua ready */
	LuaEngine();
	~LuaEngine();
	
	/* Loads a script */
	int LoadLuaScript(string lua_script);
	
	/* Runs the superscene */
	void Run(int time_now);
};

#endif