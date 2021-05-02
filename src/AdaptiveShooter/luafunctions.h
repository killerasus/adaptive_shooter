/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   1:44
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter\luafunctions.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter
	file base:	luafunctions
	file ext:	h
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	Expose ClanLib functions to Lua. Registers a CL table with these functions in a Lua state's global table
*********************************************************************/
#pragma once 

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/**
 * Registers Lua helper functions at a given Lua state under the CL
 * table.
 * 
 * @param	  L		Lua state to register
 * @return	  int
 */
int RegisterLuaCLHelper(lua_State* L);
