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

#include "gtest/gtest.h"
#include "PlayerModelImpl.h"
#include "PlayerModelTest.h"
#include "AIAgentTest.h"

// Tests model comparison
TEST_F(PlayerModelTest, CompareModels) {
	// model1._traitValues[SHOOTING_RATE] = 1.0f
	// model2._traitValues[SHOOTING_RATE] = 0.5f (default)
	EXPECT_FLOAT_EQ(0.5f, model1->compare(model2));
}

// Tests agent update
TEST_F(AIAgentTest, UpdateFunction) {
	model->setName("Normal");
	aiAgent->updateStats(); // Sets aiAgent._shootingRate to 1.0f (default 0.5f)
	EXPECT_FLOAT_EQ(1.0f, aiAgent->getShootingRate());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
