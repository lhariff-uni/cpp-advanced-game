#include "header.h"
#include "DeathState.h"
#include "PsylhaEngine.h"
#include "TextContainer.h"

#include "Player.h"
#include "Button.h"
#include  "Score.h"
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
DeathState::DeathState(PsylhaEngine* pEngine)
	: State(pEngine)
{
	insertHighscore();
}
DeathState::~DeathState()
{

}

void DeathState::setupBackground()
{
	SimpleImage image = ImageManager::loadImage("resource/back.png", true);
	image.renderImage(
		pEngine->getBackgroundSurface(),
		0, 0, 0, 0,
		image.getWidth(), image.getHeight()
	);

	TextContainer* text = DBG_NEW TextContainer(pEngine->getName() + ", you died!" , 45, 0xfcba03);
	pEngine->drawBackgroundString(
		pEngine->getWindowWidth() / 2 - text->getWidth() / 2, 50, text->getText().c_str(), text->getColour(),
		pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
	);
	delete text;
	text = DBG_NEW TextContainer("Score", 40, 0xd9a000);
	pEngine->drawBackgroundString(
		pEngine->getWindowWidth() / 2 - text->getWidth() / 2, 310, text->getText().c_str(), text->getColour(),
		pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
	);
	delete text;
	std::string buff = "";
	for (int i = 0; i < 6 - std::to_string(pEngine->getPoints()).length(); i++)
	{
		buff += "0";
	}
	buff += std::to_string(pEngine->getPoints());
	text = DBG_NEW TextContainer(buff, 50, 0xffe291);
	pEngine->drawBackgroundString(
		pEngine->getWindowWidth() / 2 - text->getWidth() / 2, 350, text->getText().c_str(), text->getColour(),
		pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
	);
	delete text;
}
void DeathState::setupForeground()
{
	pEngine->drawableObjectsChanged();
	pEngine->destroyOldObjects(true);
	pEngine->createObjectArray(0);
	pEngine->appendObjectToArray(DBG_NEW Player(pEngine->getWindowWidth()/2-64, 80, pEngine, false, true));
	pEngine->appendObjectToArray(DBG_NEW PlayButton(pEngine->getWindowWidth() / 2 - 500 / 2, 500, pEngine, 500, 70, DBG_NEW TextContainer("play again", 40, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW MenuButton(pEngine->getWindowWidth() / 2 - 500 / 2, 580, pEngine, 500, 70, DBG_NEW TextContainer("exit to menu", 40, 0xffffff)));
	pEngine->appendObjectToArray(DBG_NEW ExitButton(pEngine->getWindowWidth() / 2 - 500 / 2, 660, pEngine, 500, 70, DBG_NEW TextContainer("exit game", 40, 0xffffff)));
}

void DeathState::insertHighscore()
{
	std::vector<std::shared_ptr<Score>> vecScore = pEngine->getScore();
	std::string buff = "";
	for (int i = 0; i < 6 - std::to_string(pEngine->getPoints()).length(); i++)
	{
		buff += "0";
	}
	buff += std::to_string(pEngine->getPoints());
	std::shared_ptr<Score> obj = std::make_shared<Score>(pEngine->getName(), buff);

	if (std::atoi(vecScore[0]->getScore().c_str()) == 0)
	{
		vecScore[0].swap(obj);
		pEngine->setScore(vecScore);

		for (int i = 0; i < vecScore.size(); i++)
		{
			std::cout << vecScore[i]->getName() << ": " << vecScore[i]->getScore() << std::endl;
		}
		return;
	}
	

	int i = 0;
	for (i = vecScore.size() - 1; i >= 0; i--)
	{
		if (pEngine->getPoints() > std::atoi(vecScore[i]->getScore().c_str())) {
			if (i != 0) {
				continue;
			}
		}
		else {
			if (i == vecScore.size() - 1) {
				return;
			}
			break;
		}
	}
	int j = i + 1;
	std::shared_ptr<Score> temp = NULL;
	while (j < vecScore.size()) {
		temp = vecScore[j];
		vecScore[j].swap(obj);
		obj.swap(temp);
		j++;
	}
	pEngine->setScore(vecScore);

	/*
	for (int i = 0; i < vecScore.size(); i++)
	{
		std::cout << vecScore[i]->getName() << ": " << vecScore[i]->getScore() << std::endl;
	}
	*/
}