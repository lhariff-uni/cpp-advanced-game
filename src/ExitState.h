#pragma once
#include "State.h"
class ExitState
	: public State
{
public:
	ExitState(PsylhaEngine* pEngine);
	~ExitState();
	void saveHighScore();
	void saveName();
};