#include "header.h"
#include "ScoreState.h"
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

ScoreState::ScoreState(PsylhaEngine* pEngine)
	: State(pEngine)
{
}
ScoreState::~ScoreState() 
{
}

void ScoreState::setupBackground()
{
	SimpleImage image = ImageManager::loadImage("resource/back.png", true);
	image.renderImage(
		pEngine->getBackgroundSurface(),
		0, 0, 0, 0,
		image.getWidth(), image.getHeight()
	);
	TextContainer* text = DBG_NEW TextContainer("Highscores", 45, 0xfcba03);//DBG_NEW TextContainer("Highscores",45, 0xfcba03);
	pEngine->drawBackgroundString(
		pEngine->getWindowWidth() / 2 - text->getWidth() / 2, 50, text->getText().c_str(), text->getColour(),
		pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
	);
	delete text;
}
void ScoreState::setupForeground()
{
	pEngine->drawableObjectsChanged();
	pEngine->destroyOldObjects(true);
	pEngine->createObjectArray(0);
	
	pEngine->appendObjectToArray(
		DBG_NEW DisplayableText(300, 160, pEngine, DBG_NEW TextContainer("name", 24, 0x999999))
	);
	
	pEngine->appendObjectToArray(
		DBG_NEW DisplayableText(900, 160, pEngine, DBG_NEW TextContainer("score", 24, 0x999999))
	);

	std::vector<std::shared_ptr<Score>> vecScore = pEngine->getScore();
	for (int i = 0; i < vecScore.size(); i++) {
		pEngine->appendObjectToArray(
			DBG_NEW DisplayableText(150, 200 + i * 100, pEngine, DBG_NEW TextContainer(std::to_string(i+1) + ". ", 45, i < 2 ? 0xff9999 : 0xffffff))
		);
		pEngine->appendObjectToArray(
			DBG_NEW DisplayableText(280, 200 + i * 100, pEngine, DBG_NEW TextContainer(vecScore.at(i)->getName(), 45, i < 2 ? 0xff0000 : 0xffffff))
		);
		pEngine->appendObjectToArray(
			DBG_NEW DisplayableText(830, 200 + i * 100, pEngine, DBG_NEW TextContainer(vecScore.at(i)->getScore(), 45, i < 2 ? 0xff0000 : 0xffffff))
		);
	}
	
	pEngine->appendObjectToArray(DBG_NEW MenuButton(650 - (35*4)/2, 680, pEngine, DBG_NEW TextContainer("back", 35, 0xffffff)));	
}