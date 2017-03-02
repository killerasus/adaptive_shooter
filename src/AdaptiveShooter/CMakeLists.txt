cmake_minimum_required( VERSION 2.8 )

include_directories( "${CMAKE_BINARY_DIR}/src/AIManager" )

if( LUA51_FOUND )
    include_directories( ${LUA_INCLUDE_DIR} )
    target_link_libraries( AIManager
        LUA_LIBRARIES
    )
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

# Missing other libraries

target_link_libraries( AdaptiveShooter AIManager )

install( TARGETS AdaptiveShooter RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin )
