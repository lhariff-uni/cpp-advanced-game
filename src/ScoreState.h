#pragma once
#include "State.h"
#include "Score.h"
#include <vector>
class ScoreState :
	public State
{
public:
	ScoreState(PsylhaEngine* pEngine);
	~ScoreState();
	void setupBackground() override;
	void setupForeground() override;
};

