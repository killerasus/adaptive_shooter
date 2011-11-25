/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   13:40
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager\playermodel.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager
	file base:	playermodel
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Interface class for player model used in AIManager framework
*********************************************************************/

class PlayerModel
{
public:
	virtual float Compare(PlayerModel* comparable) = 0;
protected:

private:

};