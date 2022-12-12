#include <iostream>
#include <lua.hpp>
using namespace std;

void readLuaArray(lua_State* L, const char* arrayName)
{
	lua_getglobal(L, arrayName); // 指定的数组入栈
	luaL_checktype(L, -1, LUA_TTABLE); // 检查是否是table
	int n = (int)luaL_len(L, -1); // 获得该table的元素个数
	for (int i = 1; i <= n; i++) // table 下标从1开始
	{
		lua_rawgeti(L, -1, i); // 取i下标的元素入栈
		cout << arrayName << '[' << i << "]: " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);

	}
}

void writeLuaArray(lua_State* L, const char* arrayName)
{
	lua_getglobal(L, arrayName);
	luaL_checktype(L, -1, LUA_TTABLE);
	int n = (int)luaL_len(L, -1);
	for (int i = 1; i <= 3; i++)
	{
		lua_pushnumber(L, 10 * i); // value 入栈
		lua_rawseti(L, -2, i + n);
	}
}

int main()
{
	lua_State* pluaState = luaL_newstate();
	luaL_openlibs(pluaState);


	luaL_dofile(pluaState, "week13_01.lua");
	writeLuaArray(pluaState, "array1");

	readLuaArray(pluaState, "array1");

	lua_close(pluaState);

	return 0;
}