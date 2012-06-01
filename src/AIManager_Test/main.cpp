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
#include "AIManagerTest.h"

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

// Tests agent insertion in AIManager
TEST_F(AIManagerTest, AIManagerInsertion){
	unsigned int before = _manager->getNumberofAgents();

	EXPECT_EQ(0, before);

	_manager->insertAgent(_agent1);
	_manager->insertAgent(_agent2);

	unsigned int after = _manager->getNumberofAgents();

	EXPECT_EQ(2, after);
}

TEST_F(AIManagerTest, AIManagerRemove){
	_manager->insertAgent(_agent1);
	_manager->insertAgent(_agent2);
	_manager->insertAgent(_agent3);

	unsigned int before = _manager->getNumberofAgents();

	_manager->removeAgent(_agent2);

	unsigned int after = _manager->getNumberofAgents();

	// 3 > 2
	EXPECT_GT(before, after);

	// _agent2 must not be deleted by AIManager
	ASSERT_TRUE( _agent2 != 0 );
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
