#pragma once
#include "State.h"
class RunState :
	public State
{
public:
	RunState(PsylhaEngine* pEngine, int skeletonCount = 0, int demonCount = 0);
	~RunState();
	void setupBackground() override;
	void setupForeground() override;
	void keyUp(int iKeyCode) override;
	void updateTiles() override;
	void mainLoop() override;
private:
	void generateRandomMap();
	int skeletonCount;
	int demonCount;
};

