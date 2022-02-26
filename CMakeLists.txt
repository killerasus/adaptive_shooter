cmake_minimum_required( VERSION 3.10 )

project( AdaptiveShooter )

# ClanLib configuring

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" )
endif()

if( LUA51_FOUND )
    include_directories( ${LUA_INCLUDE_DIR} )
endif()

if( ClanLib_FOUND )
    include_directories( ${ClanLib_INCLUDE_DIRS} )
endif()

add_subdirectory( src/AIManager )
add_subdirectory( src/AIManager_Test )
add_subdirectory( src/AdaptiveShooter )

