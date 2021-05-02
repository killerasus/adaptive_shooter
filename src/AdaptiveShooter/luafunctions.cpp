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

/**
 * Necessary to print to CLConsole, as ClanLib does not offer a 
 * standard output	
 * @param	  L		Lua state to register this function
 * @return	  int	Number of returns, in acccordance to Lua API
 */
static int l_CLconsoleprint (lua_State* L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");

	for (i=1; i<=n; i++) 
	{
		const char *s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */

		if (s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to " LUA_QL("print"));

		if (i>1) 
			clan::Console::write("\t");

		clan::Console::write(s);
		lua_pop(L, 1);  /* pop result */
	}

	clan::Console::write_line("");
	return 0;
}

/* Array of functions to be exposed to Lua */
static const struct luaL_Reg CLHelper [] = {
	{"ConsolePrint", l_CLconsoleprint},
	{NULL,NULL} /* sentinel */
};

int RegisterLuaCLHelper(lua_State* L)
{
	luaL_register(L, "CL", CLHelper);
	return 1;
}
