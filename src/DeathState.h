#pragma once
#include "State.h"
class DeathState :
	public State
{
public:
	DeathState(PsylhaEngine* pEngine);
	~DeathState();
	void setupBackground() override;
	void setupForeground() override;
private:
	void insertHighscore();
};

