#pragma once
#include "Enemy.h"
class Skeleton :
	public Enemy
{
public:
	Skeleton(int xStart, int yStart, PsylhaEngine* pEngine, Player* player);
	~Skeleton();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
private:
	std::string fp;
};

