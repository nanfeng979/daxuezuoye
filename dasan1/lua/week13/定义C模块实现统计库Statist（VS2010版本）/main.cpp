#include<iostream>
#include<lua.hpp>


//处理错误函数，发生错误时，就打印一条错误消息，然后关闭lua状态。
void error(lua_State *L,const char *fmt,...)
{
	va_list argp;
	//将字符串读入到参数列表
	va_start(argp,fmt);
	vfprintf(stderr,fmt,argp);
	//参数列表清
	va_end(argp);
	//关闭lua状态
	lua_close(L);

	system("PAUSE");//按任意键继续...

	exit(EXIT_FAILURE);
}

int l_Avg(lua_State *L){//平均数
	int i,n;
	double sum = 0;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		sum+= lua_tonumber(L,-1);
		lua_pop(L,1);
	}
	lua_pushnumber(L,sum/n);
	return 1;
}

int l_Count(lua_State *L){//计数
	int n;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	lua_pushnumber(L,n);
	return 1;
}
int l_Sum(lua_State *L){//求和
	int i,n;
	double sum = 0;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		sum+= lua_tonumber(L,-1);
		lua_pop(L,1);
	}
	lua_pushnumber(L,sum);
	return 1;
}
int l_Max(lua_State *L){//最大值
	int i,n;
	double max = 0;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		if(max < lua_tonumber(L,-1)){
			max = lua_tonumber(L,-1);
		}
		lua_pop(L,1);
	}
	lua_pushnumber(L,max);
	return 1;
}
int l_Min(lua_State *L){//最小值
	int i,n;
	double min = 0;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		if(i==1){
			min = lua_tonumber(L,-1);
		}else if(min > lua_tonumber(L,-1)){
			min = lua_tonumber(L,-1);
		}
		lua_pop(L,1);
	}
	lua_pushnumber(L,min);
	return 1;
}
int l_Varp(lua_State *L){//方差
	int i,n;
	//double avg=l_Avg(L);
	double varp = 0;
	double avg = 9;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		avg += (lua_tonumber(L,-1)/n);
		lua_pop(L,1);
	}
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		double y = lua_tonumber(L,-1);
		varp += ((y/avg)*(y/avg));
		lua_pop(L,1);
	}

	lua_pushnumber(L,varp/n);

	return 1;
}
int l_StdDevP(lua_State *L){//标准差
	int i,n;
	//double avg=l_Avg(L);
	double varp = 0;
	double avg = 9;
	double StdDevp ;
	luaL_checktype(L,1,LUA_TTABLE);
	n = lua_objlen(L,1);
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		avg += (lua_tonumber(L,-1)/n);
		lua_pop(L,1);
	}
	for(i=1;i<=n;i++){
		lua_pushinteger(L,i);
		lua_gettable(L,-2);
		double y = lua_tonumber(L,-1);
		varp += ((y/avg)*(y/avg));
		lua_pop(L,1);
	}
	StdDevp = sqrt(varp);
	lua_pushnumber(L,StdDevp);
	return 1;
}


int main( )
{
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);

	luaL_Reg Statist[] = {
		{"Count",l_Count},
		{"Avg",l_Avg},
		{"Sum",l_Sum},
		{"Max",l_Max},
		{"Min",l_Min},
		{"Varp",l_Varp},
		{"StdDevP",l_StdDevP},
		{NULL,NULL}
	};

	luaL_register(L,"Statist",Statist);

	luaL_dofile(L,"map.lua");

	lua_close(L);

	system("PAUSE");//按任意键继续...

	return 0;
}