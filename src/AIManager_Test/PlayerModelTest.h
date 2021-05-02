/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:49
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test\PlayerModelTest.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test
	file base:	PlayerModelTest
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Test class (fixture) for PlayerModelImpl for GTest framework
*********************************************************************/
#pragma once

#include "gtest/gtest.h"
#include "PlayerModelImpl.h"

/**
 * Fixture class for Google Test framework
 */
class PlayerModelTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	PlayerModelTest(){
		model1 = new PlayerModelImpl(3.5f, 1.0f);
		model2 = new PlayerModelImpl(0.5f, 1.0f);

		model1->setName("Normal");
		model2->setName("Easy");
	}

	virtual ~PlayerModelTest(){
		delete model1;
		delete model2;
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	/*virtual void SetUp(){

	}

	virtual void TearDown(){

	}*/

	// Objects declared here can be used by all tests in the test case for Foo.
	PlayerModelImpl* model1;
	PlayerModelImpl* model2;

private:
};
