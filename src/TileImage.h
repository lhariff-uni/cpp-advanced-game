#pragma once
#include "SimpleImage.h"
#include <vector>

class TileImage
{
public:
	TileImage(std::string strURL, int frames, bool anim = true)
	{
		path = strURL;
		this->frames = frames;
		this->anim = anim;
		playerCollision = false;
	}
	~TileImage() {}
	//void virtDraw();
	void virtDoUpdate(int iCurrentTime)
	{
		if (anim) {
			int iTick = iCurrentTime / 100;
			int iFrame = iTick % 30;
			image = ImageManager::loadImage(path + std::to_string(iFrame % frames) + ".png", true);
		}
		else {
			image = ImageManager::loadImage(path, true);
		}

		if (playerCollision) {
			playerCollision = false;
			doAction();
		}
	}
	SimpleImage getImage() { return image; }
	std::string getPath() { return path; }
	void setPath(std::string img) { path = img; }
	int getX() { return xPos; }
	int getY() { return yPos; }
	void setX(int x) { xPos = x; }
	void setY(int y) { yPos = y; }

	void setPlayerCollision(bool col) { playerCollision = col; }
	virtual void doAction() { }
protected:
	SimpleImage image;
	std::string path;
	int frames;
	bool anim;

	bool playerCollision;
	int xPos;
	int yPos;
};

class ButtonTile
	: public TileImage
{
public:
	ButtonTile(std::string strURL, std::vector<TileImage*> fountain)
		: TileImage(strURL,0,false)
	{
		this->fountain = fountain;
	}
	~ButtonTile() {}
	void doAction() override
	{
		if (fountain[0]->getPath().find("red") == std::string::npos)
		{
			fountain[0]->setPath("resource/tile/redfountain/mid");
			fountain[1]->setPath("resource/tile/redfountain/bottom");
		}
		else {
			fountain[0]->setPath("resource/tile/bluefountain/mid");
			fountain[1]->setPath("resource/tile/bluefountain/bottom");
		}
	}
private:
	std::vector<TileImage*> fountain;
};