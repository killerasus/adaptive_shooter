cmake_minimum_required( VERSION 3.12 )

set( ClanLib_MAJOR_VERSION 3 )
set( ClanLib_MINOR_VERSION 0 )

find_package( ClanLib REQUIRED COMPONENTS App Display GL Sound )

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
)

target_link_libraries( AdaptiveShooter PRIVATE
    AIManager
)

if( LUA51_FOUND )
    target_link_libraries( AdaptiveShooter PRIVATE
        ${LUA_LIBRARIES}
    )
endif()

if( ClanLib_FOUND )
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
