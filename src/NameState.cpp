#include "header.h"
#include "NameState.h"
#include "PsylhaEngine.h"
#include "TextContainer.h"
#include "DisplayableText.h"
#include "Button.h"

#include "MenuState.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

NameState::NameState(PsylhaEngine* pEngine)
	: State(pEngine)
{

}
NameState::~NameState()
{

}

void NameState::setupBackground()
{
	SimpleImage image = ImageManager::loadImage("resource/back.png", true);
	image.renderImage(
		pEngine->getBackgroundSurface(),
		0, 0, 0, 0,
		image.getWidth(), image.getHeight()
	);
	pEngine->drawBackgroundRectangle(200, 230, 1100, 330, 0x333333);
	pEngine->drawBackgroundRectangle(205, 235, 1095, 325, 0x222222);
	TextContainer* text = DBG_NEW TextContainer("enter your name", 45, 0xfcba03);
	pEngine->drawBackgroundString(
		pEngine->getWindowWidth() / 2 - text->getWidth() / 2, 50, text->getText().c_str(), text->getColour(),
		pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
	);
	delete text;
}
void NameState::setupForeground()
{
	pEngine->drawableObjectsChanged();
	pEngine->destroyOldObjects(true);
	pEngine->createObjectArray(0);
	pEngine->appendObjectToArray(
		DBG_NEW DisplayableText(215, 240, pEngine, DBG_NEW TextContainer(pEngine->getName(), 75, 0x999999), 3)
	);
	pEngine->appendObjectToArray(DBG_NEW MenuButton(200, 350, pEngine, DBG_NEW TextContainer("cancel", 25, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW SaveNameButton(910, 350, pEngine, DBG_NEW TextContainer("enter", 35, 0xffffff)));
}