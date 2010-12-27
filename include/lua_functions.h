#ifndef LUA_FUNCTIONS_H_
#define LUA_FUNCTIONS_H_

/* All functions available for Lua */
static int NewScene(lua_State *L)
{
	superscene->NewScene();
}

/* Loading audio */
static int LoadSound(lua_State *L)
{
	superscene->scene->audio.LoadSound(0, lua_tostring(L, 1));
}

/* Starting a certain audio sound or music */
static int StartSound(lua_State *L)
{
	superscene->scene->audio.StartSound(lua_tonumber(L, 1));
}

/* Initializing the audio */
static int InitAudio(lua_State *L)
{
	superscene->scene->audio.Init();
}

static int CreateParticles(lua_State *L)
{
	/* start_x, start_y */
	int answer = superscene->scene->CreateParticles(lua_tonumber(L, 1), lua_tonumber(L, 2),
	/* end_x, end_y */
	lua_tonumber(L, 3), lua_tonumber(L, 4),
	/* amount, xx */
	lua_tonumber(L, 5), lua_tonumber(L, 6),
	/* yy, zz */
	lua_tonumber(L, 7), lua_tonumber(L, 8),
	/* texture*/
	lua_tostring(L, 9));
	
	lua_pushnumber(L, answer);
	
	if (answer != -1)
	{
		cout<<"Particles created, ID: "<<answer<<"\n";
		return 1;
	}
	else
	{
		cout<<"ERROR: Particles not created."<<"\n";
		return -1;
	}
}

static int lol(lua_State *L)
{
	if (lua_tonumber(L, 1) == 1)
		cout<<"VOE VITTU!\n";
		
	cout<<"Noh\n";
	
	cout<<lua_tonumber(L, 1);
}

static int CreateObject(lua_State *L)
{
	int answer = superscene->scene->CreateObject(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3),
	lua_tonumber(L, 4), 0, lua_tostring(L, 5), lua_tonumber(L, 6), lua_tonumber(L, 7));
	
  lua_pushnumber(L, answer); // return value
	
	if (answer != -1)
	{
		cout<<"Object created, ID: "<<answer<<"\n";
		return 1;
	}
	else
	{
		cout<<"ERROR: Object not created."<<"\n";
		return -1;
	}
	
}

static int CreatePlatform(lua_State *L)
{
	int answer = superscene->scene->CreatePlatform(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
	
  lua_pushnumber(L, answer); // return value
	
	if (answer != -1)
	{
		cout<<"Object created, ID: "<<answer<<"\n";
		return 1;
	}
	else
	{
		cout<<"ERROR: Object not created."<<"\n";
		return -1;
	}
}

#endif
