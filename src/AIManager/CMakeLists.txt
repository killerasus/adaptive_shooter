cmake_minimum_required(VERSION 3.0)

add_library( AIManager STATIC
   AIAgent.cpp
   AIManager.cpp
   PlayerModel.cpp 
)

find_package(Lua51 REQUIRED)

if (LUA51_FOUND)
    include_directories( ${LUA_INCLUDE_DIR} )
    #message( STATUS ${LUA_INCLUDE_DIR} )
    target_link_libraries( AIManager
        LUA_LIBRARIES
    ) 
endif()
