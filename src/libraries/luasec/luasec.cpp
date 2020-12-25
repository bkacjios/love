/**
 * Copyright (c) 2006-2019 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "luasec.h"

// LuaSocket
extern "C" {
#include "libluasec/ssl.h"
#include "libluasec/config.h"
#include "libluasec/context.h"
#include "libluasec/x509.h"
}

// Quick macro for adding functions to 
// the preloder.
#define PRELOAD(name, function) \
	lua_getglobal(L, "package"); \
	lua_getfield(L, -1, "preload"); \
	lua_pushcfunction(L, function); \
	lua_setfield(L, -2, name); \
	lua_pop(L, 2);	

namespace love
{
namespace luasec
{

int __open(lua_State * L)
{

	// Preload code from LuaSocket.
	PRELOAD("ssl.core", luaopen_ssl_core);
	PRELOAD("ssl.config", luaopen_ssl_config);
	PRELOAD("ssl.context", luaopen_ssl_context);
	PRELOAD("ssl.x509", luaopen_ssl_x509);

	PRELOAD("ssl", __open_luasec_ssl);
	PRELOAD("ssl.https", __open_luasec_https);

	// No need to register garbage collector function.

	return 0;
}

int __open_luasec_ssl(lua_State * L)
{
	#include "libluasec/ssl.lua.h"
	return 1;
}

int __open_luasec_https(lua_State * L)
{
	#include "libluasec/https.lua.h"
	return 1;
}

} // luasocket
} // love
