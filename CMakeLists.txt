cmake_minimum_required( VERSION 3.12 )

project( AdaptiveShooter LANGUAGES C CXX )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} )

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
# ClanLib 3.0 Dependency Management
# ==============================================================================

# Auto-fetch ClanLib submodule if missing
if( NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.ac" AND
    NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/ClanLib.sln" AND
    NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/Sources" )
    if( GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git" )
        message( STATUS "Fetching ClanLib 3.0 via git submodule update..." )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE _git_res
        )
    endif()
    # Fallback: shallow clone if submodule wasn't registered in git index
    if( NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.ac" AND
        NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/Sources" )
        if( GIT_FOUND )
            message( STATUS "Cloning ClanLib 3.0 into dependencies/clanlib..." )
            execute_process(
                COMMAND ${GIT_EXECUTABLE} clone --depth 1 -b vs2019-patch
                    https://github.com/killerasus/ClanLib.git
                    "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                RESULT_VARIABLE _git_res
            )
        endif()
    endif()
endif()

# Check if ClanLib is already available (system install or cached prefix)
find_package( ClanLib QUIET COMPONENTS App Display GL Sound )

if( NOT ClanLib_FOUND )

    # ---- Linux / UNIX: autobuild into local prefix ----
    if( UNIX AND ( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.ac" OR
                   EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/autogen.sh" ) )

        set( _CLANLIB_PREFIX "${CMAKE_BINARY_DIR}/external/clanlib" )

        if( NOT EXISTS "${_CLANLIB_PREFIX}/include/ClanLib/core.h" )
            message( STATUS "============================================================" )
            message( STATUS "ClanLib 3.0: compiling from submodule → ${_CLANLIB_PREFIX}" )
            message( STATUS "============================================================" )
            file( MAKE_DIRECTORY "${_CLANLIB_PREFIX}" )

            if( NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure" )
                message( STATUS "[ClanLib] Running ./autogen.sh ..." )
                execute_process(
                    COMMAND ./autogen.sh
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                    RESULT_VARIABLE _res )
            endif()

            if( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure" )
                message( STATUS "[ClanLib] Running ./configure ..." )
                execute_process(
                    COMMAND ./configure
                        --prefix=${_CLANLIB_PREFIX}
                        --disable-clanSqlite  --disable-clanNetwork
                        --disable-clanMikMod  --disable-clanVorbis
                        --disable-clanRegExp  --disable-shared --enable-static
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                    RESULT_VARIABLE _res )
                if( NOT _res EQUAL 0 )
                    message( FATAL_ERROR "[ClanLib] ./configure failed (${_res}). "
                        "Ensure prerequisites are installed:\n"
                        "  sudo apt-get install automake libtool "
                        "libfreetype6-dev libfontconfig1-dev libgl1-mesa-dev "
                        "libxrender-dev libasound2-dev" )
                endif()

                include( ProcessorCount )
                ProcessorCount( _NPROC )
                if( NOT _NPROC OR _NPROC EQUAL 0 )
                    set( _NPROC 2 )
                endif()
                message( STATUS "[ClanLib] make -j${_NPROC} ..." )
                execute_process(
                    COMMAND make -j${_NPROC}
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                    RESULT_VARIABLE _res )
                if( NOT _res EQUAL 0 )
                    message( FATAL_ERROR "[ClanLib] make failed (${_res})." )
                endif()

                message( STATUS "[ClanLib] make install → ${_CLANLIB_PREFIX}" )
                execute_process(
                    COMMAND make install
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                    RESULT_VARIABLE _res )
                if( NOT _res EQUAL 0 )
                    message( FATAL_ERROR "[ClanLib] make install failed (${_res})." )
                endif()
            endif()
        endif()

        set( CLANLIB_ROOT_DIR "${_CLANLIB_PREFIX}" CACHE PATH "ClanLib install prefix" FORCE )

    # ---- Windows: run configure.exe then MSBuild ----
    elseif( WIN32 AND (
            EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.exe" OR
            EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/ClanLib.sln" OR
            EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/Sources" ) )

        message( STATUS "============================================================" )
        message( STATUS "ClanLib 3.0: setting up for Windows..." )
        message( STATUS "============================================================" )

        set( _PLATFORM "Win32" )
        if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
            set( _PLATFORM "x64" )
        endif()

        set( _CONFIG "Release" )
        if( CMAKE_BUILD_TYPE MATCHES "Debug" )
            set( _CONFIG "Debug" )
        endif()

        # Locate MSBuild via vswhere
        find_program( MSBUILD_EXE msbuild )
        if( NOT MSBUILD_EXE )
            find_program( _VSWHERE vswhere
                PATHS "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/Installer" )
            if( _VSWHERE )
                execute_process(
                    COMMAND ${_VSWHERE} -latest -requires Microsoft.Component.MSBuild
                        -find "MSBuild/**/Bin/MSBuild.exe"
                    OUTPUT_VARIABLE _VSWHERE_OUT OUTPUT_STRIP_TRAILING_WHITESPACE )
                if( EXISTS "${_VSWHERE_OUT}" )
                    set( MSBUILD_EXE "${_VSWHERE_OUT}" )
                endif()
            endif()
        endif()

        # Run configure.exe (GUI-less, background) only when ClanLib.sln absent
        if( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.exe" AND
            NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/ClanLib.sln" )
            message( STATUS "[ClanLib] Generating ClanLib.sln via configure.exe..." )
            execute_process(
                COMMAND "${CMAKE_SOURCE_DIR}/dependencies/clanlib/configure.exe"
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                RESULT_VARIABLE _res )
        endif()

        # Build with MSBuild
        if( EXISTS "${CMAKE_SOURCE_DIR}/dependencies/clanlib/ClanLib.sln" AND MSBUILD_EXE )
            message( STATUS "[ClanLib] MSBuild ${_CONFIG}|${_PLATFORM}..." )
            execute_process(
                COMMAND ${MSBUILD_EXE} ClanLib.sln
                    /p:Configuration=${_CONFIG} /p:Platform=${_PLATFORM} /m
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
                RESULT_VARIABLE _res )
            if( NOT _res EQUAL 0 )
                message( WARNING "[ClanLib] MSBuild exited with ${_res}." )
            endif()
        endif()

        set( CLANLIB_ROOT_DIR "${CMAKE_SOURCE_DIR}/dependencies/clanlib"
             CACHE PATH "ClanLib install prefix" FORCE )

    endif()

endif()

# Final import — required
find_package( ClanLib REQUIRED COMPONENTS App Display GL Sound )

# ==============================================================================
# Project Subdirectories
# ==============================================================================
add_subdirectory( src/AIManager )
add_subdirectory( src/AdaptiveShooter )
