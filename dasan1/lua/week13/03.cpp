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
		lua_rawseti(L, -2, i + n); // 写入数据
	}
}

// lua数组变换
int CforLUA_arrayTransformation(lua_State* L)
{
	// 第一个参数必须是table(t)
	luaL_checktype(L, 1, LUA_TTABLE);
	// 第二个参数必须是函数(f)
	luaL_checktype(L, 2, LUA_TFUNCTION);
	// 获取table的大小
	int n = (int)luaL_len(L, 1);

	for (int i = 1; i <= n; i++)
	{
		// 压入f => 将要调用的函数入栈  // f -> f(t[i]) -> return f(t[i]) -> new t[i]
		lua_pushvalue(L, 2);
		// 压入t[i] => 将要使用的实参入栈
		lua_rawgeti(L, 1, i);
		// 调用f(t[i]) => 函数调用
		lua_call(L, 1, 1);
		// t[i] = 结果 => 修改数组元素的值
		lua_rawseti(L, 1, i);
	}

	return 0; // 无返回值
}

// 求lua数组平均值
static int CforLUA_AVG(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE); // 检查栈底是否是table类型
	int n = (int)luaL_len(L, 1); // 获取table的长度
	double sum = 0;
	for (int i = 1; i <= n; i++)
	{
		lua_pushinteger(L, i); // 将table的key值入栈
		lua_gettable(L, -2); // 将table的key值出栈，到-2的table寻找value，再将value入栈
		sum += lua_tonumber(L, -1); // 读-1栈，即上一步执行后的value
		lua_pop(L, 1); // 删除上一步指向的value
	}
	lua_pushnumber(L, sum / n);

	return 1;
}

// 求lua数组平均值，使用lua_rawgeti(L, t, key)
static int CforLUA_AVGRAW(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	int n = (int)luaL_len(L, 1);
	double sum = 0;
	for (int i = 1; i <= n; i++)
	{
		lua_rawgeti(L, 1, i);
		sum += lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	lua_pushnumber(L, sum / n);

	return 1;
}

// 字符串分割
int CforLUA_split(lua_State* L)
{
	const char* pSrc = luaL_checkstring(L, 1);
	const char* pSep = luaL_checkstring(L, 2);
	const char* pSepLocation = NULL;
	lua_newtable(L); // 在虚拟栈创建空表，用于存放结果
	int i = 1;
	while ((pSepLocation = strchr(pSrc, *pSep)) != NULL)
	{
		lua_pushlstring(L, pSrc, pSepLocation - pSrc);
		lua_rawseti(L, -2, i++);
		pSrc = pSepLocation + 1;
	}

	lua_pushstring(L, pSrc);
	lua_rawseti(L, -2, i);

	return 1; // 1个返回值，即整个数组
}

// 转换为大写字母
int CforLUA_upper(lua_State* L)
{
	size_t len;
	luaL_Buffer buf;
	const char* s = luaL_checklstring(L, 1, &len);
	luaL_buffinit(L, &buf);
	for (size_t i = 0; i < len; i++)
	{
		luaL_addchar(&buf, toupper((unsigned char)(s[i])));
	}
	luaL_pushresult(&buf);

	return 1;
}

int CforLUA_lower(lua_State* L)
{
	size_t len;
	luaL_Buffer buf;
	const char* s = luaL_checklstring(L, 1, &len);
	luaL_buffinit(L, &buf);
	for (size_t i = 0; i < len; i++)
	{
		luaL_addchar(&buf, tolower((unsigned char)(s[i])));
	}
	luaL_pushresult(&buf);

	return 1;
}


int main()
{
	lua_State* pluaState = luaL_newstate();
	luaL_openlibs(pluaState);
	lua_register(pluaState, "arrayTransformation", CforLUA_arrayTransformation);
	lua_register(pluaState, "avege", CforLUA_AVG);
	lua_register(pluaState, "avegeraw", CforLUA_AVGRAW);
	lua_register(pluaState, "split", CforLUA_split);
	lua_register(pluaState, "upper", CforLUA_upper);
	lua_register(pluaState, "lower", CforLUA_lower);

	luaL_dofile(pluaState, "week13_01.lua");

	lua_close(pluaState);

	return 0;
}