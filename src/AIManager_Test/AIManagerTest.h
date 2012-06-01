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

#include "AIManager.h"
#include "AIAgentImpl.h"
#include "PlayerModelImpl.h"
#include "gtest/gtest.h"

class AIManagerTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	AIManagerTest(){
		_manager = new AIManager( NULL );
		_model1 = new PlayerModelImpl(0.3f, 0.3f);
		_agent1 = new AIAgentImpl(_model1);
		_agent2 = new AIAgentImpl(_model1);
		_agent3 = new AIAgentImpl(_model1);
	}

	virtual ~AIManagerTest()
	{
		delete _agent3;
		delete _agent2;
		delete _agent1;
		delete _model1;
		delete _manager;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
	AIManager* _manager;
	AIAgentImpl* _agent1;
	AIAgentImpl* _agent2;
	AIAgentImpl* _agent3;
	PlayerModelImpl* _model1;
};

#endif
