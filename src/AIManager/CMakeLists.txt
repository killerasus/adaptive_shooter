cmake_minimum_required( VERSION 3.12 )

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

target_include_directories( AIManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if( LUA51_FOUND )
    target_link_libraries( AIManager PUBLIC
        ${LUA_LIBRARIES}
    )
    if( LUA_INCLUDE_DIR )
        target_include_directories( AIManager PUBLIC
            ${LUA_INCLUDE_DIR}
        )
    endif()
endif()

set_property( TARGET AIManager PROPERTY FOLDER "AIManager" )

install( TARGETS AIManager ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/bin/lib )
