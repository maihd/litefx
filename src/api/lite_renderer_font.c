#include "lite_api.h"
#include "lite_rencache.h"
#include "lite_renderer.h"


static int f_load(lua_State* L)
{
    LiteStringView	filename = lua_checkstringview(L, 1);
    float			size     = (float)luaL_checknumber(L, 2);
    LiteFont**		self     = lua_newuserdata(L, sizeof(*self));
    luaL_setmetatable(L, API_TYPE_FONT);
    *self = lite_load_font(filename, size);
    if (!*self)
    {
        luaL_error(L, "failed to load font");
    }
    return 1;
}


static int f_set_tab_width(lua_State* L)
{
    LiteFont** self = luaL_checkudata(L, 1, API_TYPE_FONT);
    int32_t    n    = luaL_checkinteger(L, 2);
    lite_set_font_tab_width(*self, n);
    return 0;
}


static int f_gc(lua_State* L)
{
    LiteFont** self = luaL_checkudata(L, 1, API_TYPE_FONT);
    if (*self)
    {
        lite_rencache_free_font(*self);
    }
    return 0;
}


static int f_get_width(lua_State* L)
{
    LiteFont**		self = luaL_checkudata(L, 1, API_TYPE_FONT);
    LiteStringView	text = lua_checkstringview(L, 2);
    lua_pushinteger(L, lite_get_font_width(*self, text));
    return 1;
}


static int f_get_height(lua_State* L)
{
    LiteFont** self = luaL_checkudata(L, 1, API_TYPE_FONT);
    lua_pushinteger(L, lite_get_font_height(*self));
    return 1;
}


static const luaL_Reg lib[] = {
    { "__gc",          f_gc            },
    { "load",          f_load          },
    { "set_tab_width", f_set_tab_width },
    { "get_width",     f_get_width     },
    { "get_height",    f_get_height    },
    { nullptr,         nullptr         },
};


int luaopen_renderer_font(lua_State* L)
{
    luaL_newmetatable(L, API_TYPE_FONT);
    luaL_setfuncs(L, lib, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    return 1;
}

//! EOF
