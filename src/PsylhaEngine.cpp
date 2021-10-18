#include "header.h"
#include "BaseEngine.h"
#include "PsylhaEngine.h"
#include "Player.h"
#include "State.h"

//#include "RunState.h"
#include "MenuState.h"
//#include "ScoreState.h"
//#include "NameState.h"
//#include "DeathState.h"
#include "ExitState.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

PsylhaEngine::PsylhaEngine()
{
	notifyObjectsAboutKeys(true);
	notifyObjectsAboutMouse(true);
	name = "n/a";
	points = 0;
	stateChanged = false;
	
	loadScores();
	loadName();
	state.reset(new MenuState(this));
}

PsylhaEngine::~PsylhaEngine(){

}

int PsylhaEngine::virtInitialise()
{
	return BaseEngine::virtInitialise();
}

void PsylhaEngine::virtSetupBackgroundBuffer()
{
	state->setupBackground();
}

int PsylhaEngine::virtInitialiseObjects()
{
	state->setupForeground();
	setAllObjectsVisible(true);
	return 0;
}

void PsylhaEngine::virtMainLoopStartIteration()
{
	state->mainLoop();
}

void PsylhaEngine::virtMainLoopPostUpdate()
{
	if (stateChanged)
	{
		if (dynamic_cast<ExitState*>(state.get())) {
			drawableObjectsChanged();
			destroyOldObjects(true);
			setExitWithCode(0);
		}
		else {
			lockAndSetupBackground();
			state->setupForeground();
			stateChanged = false;
		}
	}
}

void PsylhaEngine::virtKeyUp(int iKeyCode) 
{
	state->keyUp(iKeyCode);
}

void PsylhaEngine::virtMouseDown(int iButton, int iX, int iY) 
{
}

void PsylhaEngine::loadScores() 
{
	std::fstream file;
	std::string line;
	file.open("data/highscore.txt", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "highscore file not found: creating.." << std::endl;
		file.close();
		file.open("data/highscore.txt", std::ios::out);
		for (int i = 0; i < 5; i++) {
			file << "n/a000000\n";
		}
		file.close();
		file.open("data/highscore.txt", std::ios::in);
	}
	while (std::getline(file, line))
	{
		auto sp1 = std::make_shared<Score>(line.substr(0, 3), line.substr(3, 6));
		vecScore.push_back(sp1);
	}
	file.close();
}

void PsylhaEngine::loadName()
{
	std::fstream file;
	std::string line;
	file.open("data/name.txt", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "name file not found: creating.." << std::endl;
		file.close();
		file.open("data/name.txt", std::ios::out);
			file << "n/a\n";
		file.close();
		file.open("data/name.txt", std::ios::in);
	}
	std::getline(file, line);
	name = line.substr(0, 3);
	file.close();
}