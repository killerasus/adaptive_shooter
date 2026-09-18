cmake_minimum_required( VERSION 3.15 )

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
# Lua 5.1 Dependency Resolution
# ==============================================================================
set( LUA51_FOUND FALSE )

# Auto-initialize all submodules if Lua source is not yet present
find_package( Git QUIET )
if( GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git" )
    if( NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/src/lapi.c" AND
        NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/include/lua.h" )
        message( STATUS "Running 'git submodule update --init --recursive'..." )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        )
    endif()
endif()

# 1. Bundled submodule source → compile from source (all platforms/arch)
if( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/src/lapi.c" )
    message( STATUS "Lua 5.1: building from submodule (dependencies/lua/src)" )
    add_subdirectory( dependencies/lua )
    set( LUA_LIBRARIES lua51 )
    set( LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/lua/src" )
    set( LUA51_FOUND TRUE )
elseif( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/lapi.c" )
    message( STATUS "Lua 5.1: building from submodule (dependencies/lua)" )
    add_subdirectory( dependencies/lua )
    set( LUA_LIBRARIES lua51 )
    set( LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/lua" )
    set( LUA51_FOUND TRUE )
else()
    # 2. System-installed Lua 5.1
    find_package( Lua51 QUIET )
    # 3. Precompiled Windows x86 fallback
    if( NOT LUA51_FOUND AND WIN32 AND
        CMAKE_SIZEOF_VOID_P EQUAL 4 AND
        EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/include/lua.h" AND
        EXISTS "${CMAKE_SOURCE_DIR}/dependencies/lua/lib/Win32/lua51.lib" )
        message( STATUS "Lua 5.1: using precompiled Win32 binaries" )
        set( LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/lua/include" )
        set( LUA_LIBRARIES   "${CMAKE_SOURCE_DIR}/dependencies/lua/lib/Win32/lua51.lib" )
        set( LUA51_FOUND TRUE )
    endif()
endif()

if( NOT LUA51_FOUND )
    message( FATAL_ERROR
        "\nLua 5.1 was not found!\n"
        "Run:  git submodule update --init --recursive\n"
        "Or install:  sudo apt-get install liblua5.1-0-dev" )
endif()

include_directories( ${LUA_INCLUDE_DIR} )

# ==============================================================================
# ClanLib 3.0 Dependency Management (branch: cmake, CMake-native, no configure.exe)
# ==============================================================================
# ClanLib is built in-tree from the bundled `cmake`-branch submodule via
# add_subdirectory(). No autotools/configure, no configure.exe, no manual
# MSBuild invocation on any platform.

set( CLANLIB_SUBMODULE_DIR "${CMAKE_SOURCE_DIR}/dependencies/clanlib" )

# Auto-initialize submodules if the ClanLib CMake project is not yet present
if( NOT EXISTS "${CLANLIB_SUBMODULE_DIR}/CMakeLists.txt" )
    if( GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git" )
        message( STATUS "Running 'git submodule update --init --recursive'..." )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE _git_res
        )
    endif()
    # Fallback: shallow clone of the cmake branch if the submodule wasn't registered
    if( NOT EXISTS "${CLANLIB_SUBMODULE_DIR}/CMakeLists.txt" AND GIT_FOUND )
        message( STATUS "Cloning ClanLib (branch cmake) into dependencies/clanlib..." )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone --depth 1 -b cmake
                https://github.com/killerasus/ClanLib.git
                "${CLANLIB_SUBMODULE_DIR}"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE _git_res
        )
    endif()
endif()

# A system-installed (or custom -DCLANLIB_ROOT_DIR=...) ClanLib is still
# honored when found; otherwise the bundled submodule is built in-tree.
find_package( ClanLib QUIET COMPONENTS App Display GL Sound )

if( NOT ClanLib_FOUND )
    if( NOT EXISTS "${CLANLIB_SUBMODULE_DIR}/CMakeLists.txt" )
        message( FATAL_ERROR
            "\nClanLib CMake project not found in dependencies/clanlib.\n"
            "This project now depends on the 'cmake' branch of ClanLib.\n"
            "Run:  git submodule set-branch --branch cmake dependencies/clanlib\n"
            "      git submodule update --init --recursive\n" )
    endif()

    # The game needs App/Display/GL/Sound (upstream defaults to Core only).
    # NOTE: must use CLANLIB_BUILD_ALL — the submodule's own CMakeLists does
    # plain set(CLANLIB_BUILD_<module> OFF), which shadows per-module cache
    # values, while nothing overrides CLANLIB_BUILD_ALL.
    set( CLANLIB_BUILD_ALL ON CACHE BOOL "" FORCE )
    add_subdirectory( ${CLANLIB_SUBMODULE_DIR} )

    # The game includes umbrella headers as "ClanLib/<module>.h" while the
    # submodule keeps them as Sources/API/<module>.h. Generate a small shim
    # include tree so no game source needs to change.
    # NOTE: angle brackets are required — a quoted include would resolve to
    # the shim file itself (same basename) and #pragma-once into emptiness.
    set( CLANLIB_SHIM_DIR "${CMAKE_BINARY_DIR}/clanlib-shim" )
    file( MAKE_DIRECTORY "${CLANLIB_SHIM_DIR}/ClanLib" )
    foreach( _hdr core display gl sound application )
        file( WRITE "${CLANLIB_SHIM_DIR}/ClanLib/${_hdr}.h"
            "#pragma once\n#include <${_hdr}.h>\n" )
    endforeach()

    set( ClanLib_FOUND TRUE )
    set( ClanLib_INCLUDE_DIRS
        "${CLANLIB_SHIM_DIR}"
        "${CLANLIB_SUBMODULE_DIR}/Sources/API"
    )
    set( ClanLib_LIBRARIES
        clan30App clan30Core clan30Display clan30GL clan30Sound
    )

    # On Windows the ClanLib targets are DLLs; place them next to the game
    # binary so the loader finds them (per-config subdirs handled by CMake).
    foreach( _tgt clan30App clan30Core clan30Display clan30GL clan30Sound clan30Compute )
        if( TARGET ${_tgt} )
            set_target_properties( ${_tgt} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
        endif()
    endforeach()
endif()

if( NOT ClanLib_FOUND )
    message( FATAL_ERROR
        "\nClanLib 3.0 was not found!\n"
        "If using git submodules, make sure the 'cmake' branch is checked out:\n"
        "    git submodule set-branch --branch cmake dependencies/clanlib\n"
        "    git submodule update --init --recursive\n"
        "You can also specify a system ClanLib location with:\n"
        "    cmake -B build -DCLANLIB_ROOT_DIR=<path-to-clanlib>\n" )
endif()

# ==============================================================================
# Project Subdirectories
# ==============================================================================
add_subdirectory( src/AIManager )
add_subdirectory( src/AdaptiveShooter )
