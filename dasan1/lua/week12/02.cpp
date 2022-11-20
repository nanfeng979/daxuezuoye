#include <lua.hpp>
#include <iostream>
using namespace std;

void SecondFun(lua_State* L, double* result, int argnum, ...)
{
	lua_getglobal(L, "SecondFun");

	va_list argptr;
	va_start(argptr, argnum);
	for (int i = 0; i < argnum; i++)
	{
		double a = va_arg(argptr, double);
		lua_pushnumber(L, a);
	}
	va_end(argptr);

	if (lua_pcall(L, argnum, 2, 0) != 0)
	{
		luaL_error(L, "error ", lua_tostring(L, -1));
	}
	if (!lua_isnumber(L, -1))
	{
		luaL_error(L, "error ", lua_tostring(L, -1));
	}

	for (int i = 0; i < 2; i++)
	{
		result[i] = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}
}

int main()
{
	lua_State* pluaState = luaL_newstate();
	luaL_openlibs(pluaState);

	if (luaL_dofile(pluaState, "func.lua"))
		luaL_error(pluaState, "\'%s\'", lua_tostring(pluaState, -1));

	double result[2];
	SecondFun(pluaState, result, 3, 4.0, 5.0, 6.0);

	cout << "和：" << result[1] << endl;
	cout << "积：" << result[0] << endl;

	lua_close(pluaState);

	return 0;
}