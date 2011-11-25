/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:03
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test\main.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test
	file base:	main
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Main for unit testing of AIManager lib
*********************************************************************/

#include "aimanager.h"
#include "gtest/gtest.h"
#include "PlayerModelTest.h"

// Tests that the Foo::Bar() method does Abc.
TEST_F(PlayerModelTest, CompareModels) {
	EXPECT_EQ(3.0f, model1.Compare(&model2));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}