cmake_minimum_required( VERSION 3.10 )

find_package(GTest CONFIG REQUIRED)

if( GTest_FOUND )
	include_directories( ${GTEST_INCLUDE_DIR} )
	include(GoogleTest)
endif()

set( HEADERS
	AIAgentImpl.h
	AIAgentTest.h
	AIManagerTest.h
	PlayerModelImpl.h
	PlayerModelTest.h
)

set( SOURCES
	AIAgentImpl.cpp
	main.cpp
	PlayerModelImpl.cpp
)

source_group( "headers" FILES ${HEADERS} )
source_group( "sources" FILES ${SOURCES} )

add_executable(  AIManager_Test
    ${HEADERS}
    ${SOURCES}
)

set_property( TARGET AIManager_Test PROPERTY CXX_STANDARD 11 )
set_property( TARGET AIManager_Test PROPERTY CXX_STANDARD_REQUIRED ON )

target_include_directories( AIManager_Test PRIVATE ${LUA_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src" )
target_link_libraries( AIManager_Test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main AIManager )

gtest_discover_tests( AIManager_Test )

