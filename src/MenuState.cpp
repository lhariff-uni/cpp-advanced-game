#include "header.h"
#include "MenuState.h"
#include "PsylhaEngine.h"
#include "Button.h"
#include "Player.h"

#include "NameState.h"
#include "ScoreState.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

MenuState::MenuState(PsylhaEngine* pEngine)
	: State(pEngine)
{
}
MenuState::~MenuState() {

}

void MenuState::setupBackground()
{
	SimpleImage image = ImageManager::loadImage("resource/back.png", true);
	image.renderImage(
		pEngine->getBackgroundSurface(),
		0, 0, 0, 0,
		image.getWidth(), image.getHeight()
	);
	image = ImageManager::loadImage("resource/title.png", false);
	image.renderImageWithMask(
		pEngine->getBackgroundSurface(), 0, 0,
		pEngine->getWindowWidth() / 2 - image.getWidth() / 2, 50,
		image.getWidth(), image.getHeight(),
		0x000000
	);
	pEngine->drawBackgroundOval(130, 475, 258, 490, 0x222222);
	
	pEngine->drawBackgroundString(
		150, 500, pEngine->getName().c_str(), 0xffffff,
		pEngine->getFont("Tecmo Bowl.ttf", 32)
	);
	
}
void MenuState::setupForeground()
{
	pEngine->drawableObjectsChanged();
	pEngine->destroyOldObjects(true);
	pEngine->createObjectArray(0);
	pEngine->appendObjectToArray(DBG_NEW PlayButton(pEngine->getWindowWidth() / 2 - 500 / 2, 250, pEngine, 500, 70, DBG_NEW TextContainer("start game", 40, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW ScoreButton(pEngine->getWindowWidth() / 2 - 500 / 2, 330, pEngine, 500, 70, DBG_NEW TextContainer("highscore", 40, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW ExitButton(pEngine->getWindowWidth() / 2 - 500 / 2, 490, pEngine, 500, 70, DBG_NEW TextContainer("exit", 40, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW NameButton(138, 535, pEngine, DBG_NEW TextContainer("edit name", 10, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW Player(150, 260, pEngine, false, true));
}

void MenuState::mouseDown(int iButton)
{
}
