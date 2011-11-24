/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   1:43
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\luafunctions.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	luafunctions
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of luafunctions.h methods
*********************************************************************/

#include "luafunctions.h"
#include <ClanLib/core.h>

/************************************************************************/
/* Necessary to print to Console, as ClanLib does not offer a           */
/* standard output													    */
/************************************************************************/
static int l_CLconsoleprint (lua_State* L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to "
			LUA_QL("print"));
		if (i>1) CL_Console::write("\t");
		CL_Console::write(s);
		lua_pop(L, 1);  /* pop result */
	}
	CL_Console::write_line("");
	return 0;
}

/************************************************************************/
/* Registers Lua helper functions at a Lua state
/************************************************************************/
void RegisterLuaCLConsolePrint(lua_State* L)
{
	lua_pushcfunction(L, l_CLconsoleprint);
	lua_setglobal(L, "CLConsolePrint");
}