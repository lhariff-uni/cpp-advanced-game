#pragma once
class PsylhaEngine;
class State
{
public:
	State(PsylhaEngine* pEngine)
	{
		this->pEngine = pEngine;
	}
	~State() {}
	virtual void setupBackground(){}
	virtual void setupForeground(){}
	virtual void keyUp(int iKeyCode) {}
	virtual void mouseDown(int iButton) {}
	virtual void updateTiles() {}
	virtual void mainLoop() { updateTiles(); }
protected:
	PsylhaEngine* pEngine;
};


