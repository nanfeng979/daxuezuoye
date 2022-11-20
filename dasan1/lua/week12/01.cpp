#include <lua.hpp>
#include <iostream>
using namespace std;

void func(lua_State* L, int& a, int& b, int& c, int& d)
{
	lua_getglobal(L, "luafunc");
	if (lua_pcall(L, 0, 4, 0) != 0)
	{
		luaL_error(L, "error running function 'func': %s", lua_tostring(L, -1));
	}

	d = (int)lua_tointeger(L, -1);
	c = (int)lua_tointeger(L, -2);
	b = (int)lua_tointeger(L, -3);
	a = (int)lua_tointeger(L, -4);
	lua_pop(L, 4);
}

double twoNumberSquareSum(lua_State* L, double x, double y)
{
	lua_getglobal(L, "twoNumberSquareSum");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	if (lua_pcall(L, 2, 1, 0) != 0)
	{
		luaL_error(L, "error running function 'twoNumberSquareSum': %s", lua_tostring(L, -1));
	}

	if (!lua_isnumber(L, -1))
	{
		luaL_error(L, "function 'twoNumberSquareSum' must return a number.");
	}

	double z = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return z;
}


double maximumValue(lua_State* L, int argnum, ...)
{
	lua_getglobal(L, "maximumValue");

	va_list argptr;
	va_start(argptr, argnum);
	for (int i = 0; i < argnum; i++)
	{
		double a = va_arg(argptr, double);
		lua_pushnumber(L, a);
	}
	va_end(argptr);

	if (lua_pcall(L, argnum, 1, 0) != 0)
	{
		luaL_error(L, "error running function 'maximumValue': %s", lua_tostring(L, -1));
	}

	if (!lua_isnumber(L, -1))
	{
		luaL_error(L, "function 'findmax' must return a number", lua_tostring(L, -1));
	}

	double z = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return z;
}

int main()
{
	lua_State* pluaState = luaL_newstate();
	luaL_openlibs(pluaState);

	if (luaL_dofile(pluaState, "func.lua"))
		luaL_error(pluaState, "\'%s\'", lua_tostring(pluaState, -1));

	int a, b, c, d;
	func(pluaState, a, b, c, d);
	cout << a << ", " << b << ", " << c << ", " << d << endl;

	cout << "两个数的平方和：" << twoNumberSquareSum(pluaState, 2, 3) << endl;

	cout << "任意个数的最大值：" << maximumValue(pluaState, 4, 0.5, 0.3, 0.09, 0.91) << endl;

	lua_close(pluaState);

	return 0;
}