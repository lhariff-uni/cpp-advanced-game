#include "header.h"
#include "RunState.h"
#include "PsylhaEngine.h"
#include "Player.h"

#include "Skeleton.h"
#include "Demon.h"
#include "DisplayableText.h"

#include "PauseState.h"

#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

RunState::RunState(PsylhaEngine* pEngine, int skeletonCount, int demonCount)
	: State(pEngine)
{
	if(pEngine->isPaused())
		pEngine->unpause();
	
	this->skeletonCount = skeletonCount;
	this->demonCount = demonCount;
}
RunState::~RunState() {

}

void RunState::setupBackground()
{
	SimpleImage image = ImageManager::loadImage("resource/back.png", true);
	image.renderImage(
		pEngine->getBackgroundSurface(),
		0, 0, 0, 0,
		image.getWidth(), image.getHeight()
	);
	PsylhaTileManager& tm = pEngine->getTileManager();
	std::fstream file;
	std::string line;
	int fileNum = rand() % 20 + 1;
	file.open("maps/" + std::to_string(fileNum) + ".txt", std::ios::in);
	if (!file.is_open())
	{
		std::cout << " map file " << fileNum << " not found: creating.." << std::endl;
		file.close();
		generateRandomMap();
		file.open("maps/" + std::to_string(fileNum) + ".txt", std::ios::out);
		file << tm.getMapWidth() << "\n";
		file << tm.getMapHeight() << "\n";
		for (int y = 0; y < tm.getMapHeight(); y++) {
			for (int x = 0; x < tm.getMapWidth(); x++) {
				file << tm.getMapValue(x, y);
			}
			file << "\n";
		}
		file.close();
		file.open("maps/" + std::to_string(fileNum) + ".txt", std::ios::in);
	}
	std::getline(file, line);
	int width = std::atoi(line.c_str());
	std::getline(file, line);
	int height = std::atoi(line.c_str());
	std::vector<std::vector<int>> data(height);
	for (int y = 0; y < height; y++)
	{
		std::getline(file, line);
		data[y] = std::vector<int>(width);
		for (int x = 0; x < width; x++)
		{
			data[y][x] = line.at(x) - '0';
		}
	}
	file.close();
	tm.setMapSize(width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tm.setMapValue(x, y, data[y][x]);
		}
	}
	tm.setTopLeftPositionOnScreen(
		(pEngine->getWindowWidth() - (tm.getMapWidth() * tm.getTileWidth())) / 2,
		(pEngine->getWindowHeight() - (tm.getMapHeight() * tm.getTileHeight())) / 2
	);
	/*
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			std::cout << tm.getMapValue(j,i) << "";
		std::cout << std::endl;
	}
	*/
	tm.drawAllTiles(pEngine, pEngine->getBackgroundSurface());
}

void RunState::generateRandomMap()
{
	PsylhaTileManager& tm = pEngine->getTileManager();

	int width = rand() % 4 + (((pEngine->getWindowWidth() - (pEngine->getWindowWidth() % tm.getTileWidth())) / tm.getTileWidth()) - 3);//37;
	int height = rand() % 3 + (((pEngine->getWindowHeight() - (pEngine->getWindowHeight() % tm.getTileHeight())) / tm.getTileHeight()) - 2);//23;
	std::vector<std::vector<char>> data(height);
	for (int i = 0; i < height; i++) {
		data[i] = std::vector<char>(width);
		for (int j = 0; j < width; j++) {
			if (i % (height - 1) == 0) {
				data[i][j] = 'd';
			}
			else if (j % (width - 1) == 0) {
				data[i][j] = 'e';
			}
			else {
				data[i][j] = 'b';
			}
		}
	}
	//holes
	int w = rand() % 8 + 4;
	int h = rand() % 5 + 3;
	int tempX = (rand() % (width - w));
	int tempY = (rand() % (height - h));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (data[tempY + i][tempX + j] == 'c')
				continue;
			data[tempY + i][tempX + j] = 'c';
		}
	}
	for (int itr = 0; itr < 5; itr++) {
		int w = rand() % 4 + 1;
		int h = rand() % 4 + 1;
		int tempX = (rand() % (width - w));
		int tempY = (rand() % (height - h));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (data[tempY + i][tempX + j] == 'c')
					continue;
				data[tempY + i][tempX + j] = 'c';
			}
		}
	}

	/*
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			std::cout << data[i][j] << "";
		std::cout << std::endl;
	}
	*/

	tm.setMapSize(width + 2, height + 2);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tm.setMapValue(j, i, 0);
		}
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			tm.setMapValue(x + 1, y + 1, data[y][x] - 'a');
		}
	}

	do {
		tempX = (rand() % (tm.getMapWidth() - 4)) + 2;
	} while (tm.getMapValue(tempX, 1) != 3);
	tm.setMapValue(tempX, 1, 5);

	do {
		tempX = (rand() % (tm.getMapWidth() - 4)) + 2;
		tempY = (rand() % (tm.getMapHeight() - 4)) + 2;
	} while (tm.getMapValue(tempX, tempY) != 1 && tm.getMapValue(tempX, tempY - 1) != 5);
	tm.setMapValue(tempX, tempY, 6);

	tm.setTopLeftPositionOnScreen(
		(pEngine->getWindowWidth() - (tm.getMapWidth() * tm.getTileWidth())) / 2,
		(pEngine->getWindowHeight() - (tm.getMapHeight() * tm.getTileHeight())) / 2
	);
}

void RunState::setupForeground()
{
	pEngine->drawableObjectsChanged();
	pEngine->destroyOldObjects(true);
	pEngine->createObjectArray(0);
	pEngine->appendObjectToArray(DBG_NEW Player(pEngine));
	pEngine->appendObjectToArray(DBG_NEW PsylhaObject(10, 10, pEngine, "resource/player/emptyheart.png"));
	pEngine->appendObjectToArray(DBG_NEW PsylhaObject(10, 50, pEngine, "resource/player/emptyheart.png"));
	pEngine->appendObjectToArray(DBG_NEW PsylhaObject(10, 90, pEngine, "resource/player/emptyheart.png"));
	pEngine->appendObjectToArray(DBG_NEW PsylhaObject(10, 130, pEngine, "resource/player/emptyheart.png"));
	pEngine->appendObjectToArray(DBG_NEW PsylhaObject(10, 170, pEngine, "resource/player/emptyheart.png"));
	pEngine->appendObjectToArray(DBG_NEW DisplayableText(10, 750, pEngine, DBG_NEW TextContainer("000000", 30, 0xffffff), 6, false));
}
void RunState::mainLoop()
{
	updateTiles();
	auto p_Player = dynamic_cast<Player*>(pEngine->getDisplayableObject(0));
	PsylhaTileManager& tm = pEngine->getTileManager();
	skeletonCount -= p_Player->getSkeletonCount();
	demonCount -= p_Player->getDemonCount();
	p_Player->resetSkeletonCount();
	p_Player->resetDemonCount();
	
	if (skeletonCount < 15) {
		int iTick = pEngine->getModifiedTime();
		if (iTick % 1000 == 0) { //every second
			int tempX = 650, tempY = 400;
			do {
				tempX = (rand() % pEngine->getWindowWidth());
				tempY = (rand() % pEngine->getWindowHeight());
			} while (tm.getMapValue(tm.getMapXForScreenX(tempX), tm.getMapYForScreenY(tempY + 35)) != 1 || tm.getMapValue(tm.getMapXForScreenX(tempX + 35), tm.getMapYForScreenY(tempY + 35)) != 1);
			pEngine->appendObjectToArray(DBG_NEW Skeleton(tempX, tempY, pEngine, p_Player));
			p_Player->attach(dynamic_cast<Enemy*>(pEngine->getDisplayableObject(pEngine->getContentCount() - 1)));
			skeletonCount++;
		}
	}
	if (demonCount < 2) {
		int iTick = pEngine->getModifiedTime();
		if (iTick % 2000 == 0) { //every 2 seconds
			int tempX = 650, tempY = 400;
			do {
				tempX = (rand() % pEngine->getWindowWidth());
				tempY = (rand() % pEngine->getWindowHeight());
			} while (tm.getMapValue(tm.getMapXForScreenX(tempX), tm.getMapYForScreenY(tempY + 85)) != 1 || tm.getMapValue(tm.getMapXForScreenX(tempX + 70), tm.getMapYForScreenY(tempY + 85)) != 1);
			pEngine->appendObjectToArray(DBG_NEW Demon(tempX, tempY, pEngine, p_Player));
			p_Player->attach(dynamic_cast<Enemy*>(pEngine->getDisplayableObject(pEngine->getContentCount() - 1)));
			demonCount++;
		}
	}
	for (int i = 1; i < 6; i++) {
		if (i <= p_Player->getHealth()) {
			dynamic_cast<PsylhaObject*>(pEngine->getDisplayableObject(i))->setImage(ImageManager::get()->getImagebyURL("resource/player/fullheart.png", true/*Load*/, true/*Keep it loaded*/));
		}
		else {
			dynamic_cast<PsylhaObject*>(pEngine->getDisplayableObject(i))->setImage(ImageManager::get()->getImagebyURL("resource/player/emptyheart.png", true/*Load*/, true/*Keep it loaded*/));
		}
	}

	std::string buff = "";
	for (int i = 0; i < 6 - std::to_string(pEngine->getPoints()).length(); i++)
	{
		buff += "0";
	}
	buff += std::to_string(pEngine->getPoints());
	dynamic_cast<DisplayableText*>(pEngine->getDisplayableObject(6))->setText(buff);
}


void RunState::updateTiles()
{
	PsylhaTileManager& tm = pEngine->getTileManager();
	std::vector<TileImage*> fountain = tm.getFountain();
	SimpleImage image = NULL;
	for (int i = 0; i < fountain.size(); i++)
	{
		fountain[i]->virtDoUpdate(pEngine->getModifiedTime());
		image = fountain[i]->getImage();
		pEngine->getBackgroundSurface()->mySDLLockSurface();
		image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
			fountain[i]->getX(),
			fountain[i]->getY(),
			tm.getTileWidth(), tm.getTileHeight()
		);
		pEngine->getBackgroundSurface()->mySDLUnlockSurface();
	}
	ButtonTile* button = tm.getButton();
	button->virtDoUpdate(pEngine->getModifiedTime());
	image = button->getImage();
	pEngine->getBackgroundSurface()->mySDLLockSurface();
	image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
		button->getX(),
		button->getY(),
		tm.getTileWidth(), tm.getTileHeight()
	);
	pEngine->getBackgroundSurface()->mySDLUnlockSurface();
}

void RunState::keyUp(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE) {
		pEngine->setStateNoFlag(DBG_NEW PauseState(pEngine, skeletonCount, demonCount));
	}
}