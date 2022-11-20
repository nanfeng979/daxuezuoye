#include <lua.hpp>
#include <iostream>
using namespace std;

int C_findmax(lua_State* L)
{
	double x = lua_tonumber(L, -2);
	double y = lua_tonumber(L, -1);

	double z = x > y ? x : y;
	lua_pushnumber(L, z);

	return 1;
}

int main()
{
	lua_State* pluaState = luaL_newstate();
	luaL_openlibs(pluaState);

	lua_register(pluaState, "findmax", C_findmax);

	if (luaL_dofile(pluaState, "func.lua"))
	{
		luaL_error(pluaState, "\'%s\'", lua_tostring(pluaState, -1)); 
	}

	lua_close(pluaState);

	return 0;
}