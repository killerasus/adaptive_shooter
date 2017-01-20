cmake_minimum_required( VERSION 3.0 )

project( AdaptiveShooter )

# ClanLib configuring

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

set( ClanLib_MAJOR_VERSION 3 )
set( ClanLib_MINOR_VERSION 0 )

# You MUST define where to find ClanLib
set( ClanLib_DIR "ClanLib" CACHE STRING "ClanLib directory" )

find_package( ClanLib REQUIRED )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
endif()

if( GCC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} 
        --std=c++11
        -Wall
    " )
endif()

add_subdirectory( src/AIManager )
add_subdirectory( src/AdaptiveShooter )

