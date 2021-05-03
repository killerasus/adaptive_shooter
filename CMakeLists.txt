cmake_minimum_required( VERSION 3.10 )

project( AdaptiveShooter )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

if(MSVC)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
    set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )
    #add_compile_options( $<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
    #                     $<$<CONFIG:RelWithDebInfo>:/MT> # Runtime library: Multi-threaded                           
    #                     $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
    #                   )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" )
endif()

add_subdirectory( src/AIManager )
add_subdirectory( src/AIManager_Test )
add_subdirectory( src/AdaptiveShooter )

