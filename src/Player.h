#pragma once
#include "PsylhaActor.h"
#include <list>

class PsylhaEngine;
class Enemy;

class Player :
	public PsylhaActor
{
public:
	Player(PsylhaEngine* pEngine, bool controllable = true, bool large = false);
	Player(int xStart, int yStart, PsylhaEngine* pEngine, bool controllable = true, bool large = false);
	~Player();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	void virtMouseDown(int iButton, int iX, int iY);
	
	int getHealth() { return health; }
	void attach(Enemy* enemy);
	void detach(Enemy* enemy);
	void notify();
	void createMessage(std::string message = "Empty");
	void observerCount();

	void addSkeletonCount() { skeletonCount++; }
	void addDemonCount() { demonCount++; }
	int getSkeletonCount() { return skeletonCount; }
	int getDemonCount() { return demonCount; }
	void resetSkeletonCount() { skeletonCount = 0; }
	void resetDemonCount() { demonCount = 0; }
private:
	std::string fp;
	bool dir;
	std::string folder = "resource/player/";
	bool controllable;
	bool large;
	int health;

	bool limitButton;

	std::list<Enemy*> observerList;
	std::string message;

	int skeletonCount;
	int demonCount;
};

