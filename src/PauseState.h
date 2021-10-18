#pragma once
#include "State.h"
class PauseState :
	public State
{
public:
	PauseState(PsylhaEngine* pEngine, int skeletonCount, int demonCount);
	~PauseState();
	//void setupBackground() override;
	void setupForeground() override;
	void keyUp(int iKey) override;
private:
	int skeletonCount;
	int demonCount;
};

