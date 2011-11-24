/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   1:44
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\luafunctions.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	luafunctions
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Expose ClanLib functions to Lua. Registers a CL table with these functions in a Lua state's global table
*********************************************************************/

#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

static int l_CLconsoleprint (lua_State* L);
void RegisterLuaCLConsolePrint(lua_State* L);

#endif