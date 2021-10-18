#pragma once
#include "State.h"
class MenuState :
	public State
{
public:
	MenuState(PsylhaEngine* pEngine);
	~MenuState();
	void setupBackground() override;
	void setupForeground() override;
	void mouseDown(int iButton) override;
};

