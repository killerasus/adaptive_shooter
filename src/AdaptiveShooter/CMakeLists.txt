cmake_minimum_required( VERSION 3.15 )

set( ClanLib_MAJOR_VERSION 3 )
set( ClanLib_MINOR_VERSION 0 )

# ClanLib is resolved by the top-level CMakeLists (bundled cmake-branch
# submodule via add_subdirectory, or a system install). No find_package here:
# the imported targets / variables are already in scope.

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

target_include_directories( AdaptiveShooter PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ClanLib_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries( AdaptiveShooter PRIVATE
    AIManager
)

if( LUA51_FOUND )
    target_link_libraries( AdaptiveShooter PRIVATE
        ${LUA_LIBRARIES}
    )
endif()

if( UNIX AND NOT APPLE )
    # GameManager queries the mouse pointer (XQueryPointer) to anchor the
    # window on a visible output; needs X11 headers and lib (libx11-dev).
    find_package( X11 REQUIRED )
    target_link_libraries( AdaptiveShooter PRIVATE
        X11::X11
    )
endif()

# Prefer the in-tree cmake-branch targets; fall back to whatever a system
# FindClanLib module resolved (ClanLib_LIBRARIES).
if( TARGET clan30Core )
    target_link_libraries( AdaptiveShooter PRIVATE
        clan30App
        clan30Core
        clan30Display
        clan30GL
        clan30Sound
    )
    if( WIN32 )
        # Consumers of the ClanLib DLLs must see dllimport declarations
        # (otherwise cross-DLL data like Colorf::black is expected statically).
        target_compile_definitions( AdaptiveShooter PRIVATE CL_API_DLL )
    endif()
    if( MSVC )
        # Neutralize legacy autotools `#pragma comment(lib, "clan*-*.lib")`
        # auto-link directives in ClanLib headers (e.g. clanCore-static-mtdll.lib,
        # which the CMake build never produces). Mirrors the NODEFAULTLIB list
        # in the ClanLib cmake branch; our explicit target_link_libraries above
        # is what actually links. Must live here (not upstream) because
        # add_link_options/target_link_options do not cross directory scope.
        set( _clan_autolink_libs
            Core App Display GL Sound Database Sqlite Network GUI CSSLayout
            Scene3D Physics3D Physics2D GameIDE SWRender Compute D3D MySQL GL1 )
        foreach( _clan ${_clan_autolink_libs} )
            foreach( _variant
                "-dll.lib" "-static-mtdll.lib" "-static-mt.lib"
                "-dll-debug.lib" "-static-mtdll-debug.lib" "-static-mt-debug.lib" )
                target_link_options( AdaptiveShooter PRIVATE "/NODEFAULTLIB:clan${_clan}${_variant}" )
            endforeach()
        endforeach()
        foreach( _variant
            "-dll.lib" "-static-mtdll.lib" "-static-mt.lib"
            "-dll-debug.lib" "-static-mtdll-debug.lib" "-static-mt-debug.lib" )
            target_link_options( AdaptiveShooter PRIVATE "/NODEFAULTLIB:clanCSSLayout${_variant}" )
        endforeach()
        # Entry point is WinMain from clan30App (classic ClanLib pattern:
        # `clan::Application app(&MyApp::main);` — the game defines no main()).
        target_link_options( AdaptiveShooter PRIVATE "/SUBSYSTEM:WINDOWS" )
    endif()
elseif( ClanLib_FOUND )
    target_link_libraries( AdaptiveShooter PRIVATE
        ${ClanLib_LIBRARIES}
    )
endif()

install( TARGETS AdaptiveShooter RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin )

# Copies Script and Data directories to output directory next to binary (handles both single- and multi-config generators)
add_custom_command( TARGET AdaptiveShooter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Scripts $<TARGET_FILE_DIR:AdaptiveShooter>/Scripts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:AdaptiveShooter>/data
)
