cmake_minimum_required( VERSION 3.10 )

include(FindLua)
find_package(Lua REQUIRED)

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

target_include_directories( AIManager PRIVATE ${LUA_INCLUDE_DIR} )
target_link_libraries( AIManager PRIVATE ${LUA_LIBRARIES} ) 

set_property( TARGET AIManager PROPERTY FOLDER "${CMAKE_BINARY_DIR}/solution/AIManager" )

install( TARGETS AIManager ARCHIVE DESTINATION "${CMAKE_BINARY_DIR}/bin/lib" )
