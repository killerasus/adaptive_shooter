cmake_minimum_required(VERSION 3.10)
project(lua51 C)

# Locate Lua C source files (supporting both submodule src/ layout and flat layout)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/lapi.c")
    set(LUA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lapi.c")
    set(LUA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
else()
    message(WARNING "Lua C source files not found in ${CMAKE_CURRENT_SOURCE_DIR}. Did you run 'git submodule update --init --recursive'?")
    return()
endif()

set(LUA_CORE_SOURCES
    ${LUA_SRC_DIR}/lapi.c
    ${LUA_SRC_DIR}/lcode.c
    ${LUA_SRC_DIR}/ldebug.c
    ${LUA_SRC_DIR}/ldo.c
    ${LUA_SRC_DIR}/ldump.c
    ${LUA_SRC_DIR}/lfunc.c
    ${LUA_SRC_DIR}/lgc.c
    ${LUA_SRC_DIR}/llex.c
    ${LUA_SRC_DIR}/lmem.c
    ${LUA_SRC_DIR}/lobject.c
    ${LUA_SRC_DIR}/lopcodes.c
    ${LUA_SRC_DIR}/lparser.c
    ${LUA_SRC_DIR}/lstate.c
    ${LUA_SRC_DIR}/lstring.c
    ${LUA_SRC_DIR}/ltable.c
    ${LUA_SRC_DIR}/ltm.c
    ${LUA_SRC_DIR}/lundump.c
    ${LUA_SRC_DIR}/lvm.c
    ${LUA_SRC_DIR}/lzio.c
)

set(LUA_LIB_SOURCES
    ${LUA_SRC_DIR}/lauxlib.c
    ${LUA_SRC_DIR}/lbaselib.c
    ${LUA_SRC_DIR}/ldblib.c
    ${LUA_SRC_DIR}/liolib.c
    ${LUA_SRC_DIR}/lmathlib.c
    ${LUA_SRC_DIR}/loslib.c
    ${LUA_SRC_DIR}/ltablib.c
    ${LUA_SRC_DIR}/lstrlib.c
    ${LUA_SRC_DIR}/loadlib.c
    ${LUA_SRC_DIR}/linit.c
)

add_library(lua51 STATIC
    ${LUA_CORE_SOURCES}
    ${LUA_LIB_SOURCES}
)

target_include_directories(lua51 PUBLIC
    $<BUILD_INTERFACE:${LUA_SRC_DIR}>
    $<INSTALL_INTERFACE:include>
)

if(UNIX AND NOT APPLE)
    target_link_libraries(lua51 PRIVATE m)
    if(CMAKE_DL_LIBS)
        target_link_libraries(lua51 PRIVATE ${CMAKE_DL_LIBS})
    endif()
endif()
