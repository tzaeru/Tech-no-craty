#include "../include/lua_engine.h"
#include "../include/lua_functions.h"

LuaEngine::LuaEngine()
{
	superscene = new Superscene();
	
	/* initialize Lua */
	L = lua_open();

	/* load Lua base libraries */
	luaL_openlibs(L);
	
	/* register our functions. They are defined in lua_functions.h */
	lua_register(L, "NewScene", NewScene);
	lua_register(L, "CreateObject", CreateObject);
	lua_register(L, "CreateParticles", CreateParticles);
	lua_register(L, "CreatePlatform", CreatePlatform);
	lua_register(L, "LoadSound", LoadSound);
	lua_register(L, "StartSound", StartSound);
	lua_register(L, "InitAudio", InitAudio);
	lua_register(L, "lol", lol);
	
}

int LuaEngine::LoadLuaScript(string lua_script)
{
	/* load & run the script */
	luaL_dofile(L, lua_script.c_str());
}

void LuaEngine::Run(int time_now)
{
	superscene->Run(time_now);
}

LuaEngine::~LuaEngine()
{
	/* cleanup Lua */
	lua_close(L);

	delete superscene;
}
