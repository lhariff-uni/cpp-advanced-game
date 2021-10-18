#include "header.h"
#include "TileImage.h"
#include "ImageManager.h"

TileImage::TileImage(std::string strURL, int frames, bool anim)
{
	path = strURL;
	this->frames = frames;
	this->anim = anim;
	playerCollision = false;
}
TileImage::~TileImage()
{

}
/*
void TileImage::virtDraw()
{

}
*/

void TileImage::virtDoUpdate(int iCurrentTime)
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
		doAction();
	}
}
