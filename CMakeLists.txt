cmake_minimum_required( VERSION 3.12 )

project( AdaptiveShooter LANGUAGES C CXX )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# C++ Standard configuration
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

if( MSVC )
    add_compile_options( /W4 )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" )
    add_compile_options( -Wall )
endif()

# ==============================================================================
# Lua 5.1 Dependency Resolution & Automated Submodule Handling
# ==============================================================================
set( LUA51_FOUND FALSE )

# Auto-initialize Lua submodule if missing and git is present
find_package( Git QUIET )
if( GIT_FOUND AND NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/src/lapi.c" AND NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/include/lua.h" )
    if( EXISTS "${CMAKE_SOURCE_DIR}/.git" )
        message( STATUS "Lua submodule not initialized. Running 'git submodule update --init --recursive'..." )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE _git_res
        )
    endif()
endif()

# 1. Check if Lua submodule source is available
if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/src/lapi.c" OR EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/lapi.c" )
    message( STATUS "Using bundled Lua 5.1 from submodule in dependencies/lua" )
    add_subdirectory( dependencies/lua )
    set( LUA_LIBRARIES lua51 )
    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/src/lua.h" )
        set( LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/src" )
    else()
        set( LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua" )
    endif()
    set( LUA51_FOUND TRUE )
else()
    # 2. Try system-installed Lua 5.1
    find_package( Lua51 QUIET )
    
    # 3. Fallback to precompiled Windows binaries if present
    if( NOT LUA51_FOUND AND WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/include/lua.h" )
        if( CMAKE_SIZEOF_VOID_P EQUAL 4 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/lib/Win32/lua51.lib" )
            message( STATUS "Using precompiled 32-bit Lua 5.1 binaries from dependencies/lua" )
            set( LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/include" )
            set( LUA_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/lib/Win32/lua51.lib" )
            set( LUA51_FOUND TRUE )
        endif()
    endif()
endif()

if( NOT LUA51_FOUND )
    message( FATAL_ERROR
        "\n"
        "========================================================================\n"
        "Lua 5.1 was not found!\n"
        "AdaptiveShooter requires Lua 5.1.\n\n"
        "To fetch the Lua submodule, run:\n"
        "    git submodule update --init --recursive\n\n"
        "Or install the Lua 5.1 development package for your OS:\n"
        "    Ubuntu/Debian: sudo apt-get install liblua5.1-0-dev\n"
        "========================================================================"
    )
endif()

include_directories( ${LUA_INCLUDE_DIR} )

# ==============================================================================
# ClanLib 3.0 Dependency Resolution & Automated Submodule Build
# ==============================================================================
include( "${CMAKE_SOURCE_DIR}/cmake/ManageClanLib.cmake" )

# ==============================================================================
# Project Subdirectories
# ==============================================================================
add_subdirectory( src/AIManager )
add_subdirectory( src/AdaptiveShooter )
