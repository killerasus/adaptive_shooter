cmake_minimum_required( VERSION 2.8 )

set( HEADERS
    AIAgent.h
    AIManager.h
    PlayerModel.h
    Trait.h
)

set( SOURCES
    AIAgent.cpp
    AIManager.cpp
    PlayerModel.cpp
)

source_group( "sources" FILES ${SOURCES} )
source_group( "headers" FILES ${HEADERS} )

add_library( AIManager STATIC
    ${SOURCES}
    ${HEADERS}
)

find_package( Lua51 REQUIRED )

if( LUA51_FOUND )
    include_directories( ${LUA_INCLUDE_DIR} )
    target_link_libraries( AIManager
        LUA_LIBRARIES
    ) 
endif()

set_property( TARGET AIManager PROPERTY FOLDER "${CMAKE_BINARY_DIR}/solution/AIManager" )

install( TARGETS AIManager ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/bin/lib )
