/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:18
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager\aiagent.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager
	file base:	aiagent
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	AIAgent
*********************************************************************/
#ifndef AIAgent_h__
#define AIAgent_h__

class AIAgent
{
public:
	AIAgent();
	virtual ~AIAgent();
	virtual void updateStats() = 0;
protected:
	
private:

};

#endif // AIAgent_h__
