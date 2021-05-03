cmake_minimum_required( VERSION 3.15 )

include(FindLua)
find_package(Lua REQUIRED)

set( ClanLib_MAJOR_VERSION 3 )
set( ClanLib_MINOR_VERSION 0 )

# You MUST define where to find ClanLib
if(WIN32)
    unset( _DLL )
    set( ClanLib_DIR "${CMAKE_SOURCE_DIR}/dependencies/ClanLib" CACHE STRING "ClanLib directory" )
else()
    set( ClanLib_DIR "ClanLib" CACHE STRING "ClanLib directory" )
endif()

if(NOT WIN32)
    find_package( ClanLib REQUIRED )
else()
    set(CLANLIB_ROOT_DIR  "${CMAKE_SOURCE_DIR}/dependencies/ClanLib/" )
    set(ClanLib_INCLUDE_DIRS "${CLANLIB_ROOT_DIR}/Include" )
    find_package( ClanLib REQUIRED )
endif()

set( HEADERS
    ControllerInterface.h
    KeyboardController.h
    Shooter.h
    DynamicEntity.h
    luafunctions.h
    Shot.h
    Enemy.h
    MenuDifficulty.h
    StaticEntity.h
    Entity.h
    Menu.h
    TestEnemy.h
    Explosion.h
    MenuItem.h
    TestScene.h
    FadingScene.h
    Player.h
    TestScenePlayer.h
    GameManager.h
    PlayerModelImpl.h
    Weapon.h
    GamepadController.h
    Scene.h
)

set( SOURCES
    DynamicEntity.cpp
    luafunctions.cpp
    Shooter.cpp
    Enemy.cpp               
    main.cpp             
    Shot.cpp
    Entity.cpp              
    Menu.cpp             
    StaticEntity.cpp
    Explosion.cpp           
    MenuDifficulty.cpp   
    TestEnemy.cpp
    FadingScene.cpp         
    MenuItem.cpp         
    TestScene.cpp
    GameManager.cpp         
    Player.cpp           
    TestScenePlayer.cpp
    GamepadController.cpp   
    PlayerModelImpl.cpp  
    Weapon.cpp
    KeyboardController.cpp  
    Scene.cpp
)

source_group( "headers" FILES ${HEADERS} )
source_group( "sources" FILES ${SOURCES} )

add_executable( AdaptiveShooter
    ${HEADERS}
    ${SOURCES}
)

set_property( TARGET AdaptiveShooter PROPERTY CXX_STANDARD 11 )
set_property( TARGET AdaptiveShooter PROPERTY CXX_STANDARD_REQUIRED ON )

if(WIN32)
    set( ClanLib_LIBRARIES 
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanApp-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanCompute-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanCore-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanCSSLayout-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanD3D-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanDatabase-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanDisplay-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanGameIDE-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanGL-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanGUI-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanNetwork-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanPhysics2D-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanPhysics3D-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanScene3D-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanSound-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanSqlite-static-mt.lib"
            "${CLANLIB_ROOT_DIR}/Lib/Win32/clanSWRender-static-mt.lib"
    )

    set_property(TARGET AdaptiveShooter PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_include_directories( AdaptiveShooter PRIVATE ${LUA_INCLUDE_DIR} ${ClanLib_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/src/" )
target_link_libraries( AdaptiveShooter PRIVATE ${LUA_LIBRARIES} ${ClanLib_LIBRARIES} AIManager )

install( TARGETS AdaptiveShooter RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin )

# Copies Script and Data directories to bin directory

add_custom_command( TARGET AdaptiveShooter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Scripts ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Scripts
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data )
