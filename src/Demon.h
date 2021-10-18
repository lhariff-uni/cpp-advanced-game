#pragma once
#include "Enemy.h"
class Demon :
	public Enemy
{
public:
	Demon(int xStart, int yStart, PsylhaEngine* pEngine, Player* player);
	~Demon();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
private:
	std::string fp;
};

