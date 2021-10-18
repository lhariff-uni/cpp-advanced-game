#pragma once
#include "State.h"
class NameState :
	public State
{
public:
	NameState(PsylhaEngine* pEngine);
	~NameState();
	void setupBackground() override;
	void setupForeground() override;
};

