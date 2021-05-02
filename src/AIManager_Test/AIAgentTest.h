/********************************************************************
	created:	2012/05/29
	created:	29:5:2012   18:34
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test\AIAgentTest.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test
	file base:	AIAgentTest
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

#include "gtest/gtest.h"
#include "AIAgentImpl.h"

/**
 * Fixture class for Google Test framework
 */

class AIAgentTest : public testing::Test
{
protected:

	AIAgentTest()
	{
		model = new PlayerModelImpl(0.3f, 1.0f);
		aiAgent = new AIAgentImpl(model);
	}

	~AIAgentTest()
	{
		delete aiAgent;
		delete model;
	}
	
	PlayerModelImpl* model;
	AIAgentImpl* aiAgent;

private:

};
