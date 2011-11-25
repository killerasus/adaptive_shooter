/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:10
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test\AIManagerTest.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test
	file base:	AIManagerTest
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Test class for AIManager, holds test implementations following GTest framework
*********************************************************************/

#ifndef AIMANAGERTEST_H
#define AIMANAGERTEST_H

#include "aimanager.h"
#include "PlayerModelImpl.h"
#include "gtest/gtest.h"

class AIManagerTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	AIManagerTest();
	virtual ~AIManagerTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp();

	virtual void TearDown();

	// Objects declared here can be used by all tests in the test case for Foo.
	AIManager* _manager;
	PlayerModelImpl model1(5.0f);
	PlayerModelImpl model2(2.0f);
};

#endif
