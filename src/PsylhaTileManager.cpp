#include "header.h"
#include "PsylhaTileManager.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

PsylhaTileManager::PsylhaTileManager()
	: TileManager(32, 32)
{
	fountain.push_back(DBG_NEW TileImage("resource/tile/redfountain/mid",3));
	fountain.push_back(DBG_NEW TileImage("resource/tile/redfountain/bottom",3));
	button = DBG_NEW ButtonTile("resource/tile/button/false.png", getFountain());
}
PsylhaTileManager::~PsylhaTileManager() {
	delete fountain[0];
	delete fountain[1];
	delete button;
}

void PsylhaTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	SimpleImage image;
	int temp = 0;
	switch (getMapValue(iMapX, iMapY))
	{
	case 0: //blank / null
		break;
	case 1: // floor
		temp = rand() % 100 + 1;
		if (temp < 26) {
			temp = 1;
		}
		else if (temp < 50) {
			temp = 5;
		}
		else if (temp < 65) {
			temp = 2;
		}
		else if (temp < 70) {
			temp = 4;
		}
		else if (temp < 90) {
			temp = 3;
		}
		else if (temp < 95) {
			temp = 6;
		}
		else if (temp < 98) {
			temp = 7;
		}
		else {
			temp = 8;
		}
		image = ImageManager::loadImage("resource/tile/floor/floor_" + std::to_string(temp) + ".png", true);
		image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			this->getTileWidth(), this->getTileHeight()
		);
		
		if (getMapValue(iMapX, iMapY + 1) == 3) {
			image = ImageManager::loadImage("resource/tile/wall/wall_top_mid.png", true);
			image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight(),
				0x000000
			);
		}
		
		break;
	case 2: // holes
		if (getMapValue(iMapX, iMapY - 1) == 1 || getMapValue(iMapX, iMapY - 1) == 6) {
			image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
			image.renderImageWithMaskAndTransparency(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight()/2,
				0xffffff,50
			);
		}
		else if (getMapValue(iMapX, iMapY - 1) == 4) {
			if (getMapValue(iMapX - 1, iMapY - 1) == 1) {
				image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
				image.renderImageWithMaskAndTransparency(pEngine->getBackgroundSurface(), 0, 0,
					iStartPositionScreenX,
					iStartPositionScreenY,
					this->getTileWidth() / 4, this->getTileHeight() / 2,
					0xffffff, 100
				);
			}
			else if (getMapValue(iMapX + 1, iMapY - 1) == 1) {
				image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
				image.renderImageWithMaskAndTransparency(pEngine->getBackgroundSurface(), 0, 0,
					iStartPositionScreenX + (image.getWidth() / 4 * 3),
					iStartPositionScreenY,
					this->getTileWidth() / 4, this->getTileHeight() / 2,
					0xffffff, 100
				);
			}
		}
		break;
	case 3: // wall front + back
		if (getMapValue(iMapX-1,iMapY) == 0) {
			if (getMapValue(iMapX + 1, iMapY + 1) == 2 || getMapValue(iMapX + 1, iMapY - 1) == 2) {
				break;
			}
			image = getMapValue(iMapX, iMapY - 1) == 0 ? ImageManager::loadImage("resource/tile/wall/wall_side_mid_left.png", true)
				: ImageManager::loadImage("resource/tile/wall/wall_side_front_left.png", true);
			image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight(),
				0x000000
			);
		}
		else if (getMapValue(iMapX+1,iMapY) == 0) {
			if (getMapValue(iMapX - 1, iMapY + 1) == 2 || getMapValue(iMapX - 1, iMapY - 1) == 2) {
				break;
			}
			image = getMapValue(iMapX, iMapY - 1) == 0 ? ImageManager::loadImage("resource/tile/wall/wall_side_mid_right.png", true)
				: ImageManager::loadImage("resource/tile/wall/wall_side_front_right.png", true);
			image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight(),
				0x000000
			);
		}
		else {
			if (getMapValue(iMapX, iMapY - 1) == 2 || getMapValue(iMapX, iMapY + 1) == 2) {
				break;
			}
			image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
			image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight()
			);
			if (getMapValue(iMapX, iMapY - 1) == 0) {
				image = ImageManager::loadImage("resource/tile/wall/wall_top_mid.png", true);
				image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
					iStartPositionScreenX,
					iStartPositionScreenY - 25,
					this->getTileWidth(), this->getTileHeight(),
					0x000000
				);
			}
		}
		break;
	case 4: // wall sides
		if (getMapValue(iMapX - 1, iMapY) == 2 || getMapValue(iMapX + 1, iMapY) == 2) {
			if (getMapValue(iMapX - 1, iMapY - 1) == 1) {
				image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
				image.renderImageWithMaskAndTransparency(pEngine->getBackgroundSurface(), 0, 0,
					iStartPositionScreenX,
					iStartPositionScreenY,
					this->getTileWidth()/4, this->getTileHeight() / 2,
					0xffffff, 100
				);
			}
			else if (getMapValue(iMapX + 1, iMapY - 1) == 1) {
				image = ImageManager::loadImage("resource/tile/wall/wall_mid.png", true);
				image.renderImageWithMaskAndTransparency(pEngine->getBackgroundSurface(), 0, 0,
					iStartPositionScreenX + (image.getWidth()/4*3),
					iStartPositionScreenY, 
					this->getTileWidth() / 4, this->getTileHeight() / 2,
					0xffffff, 100
				);
			}
			break;
		}
		image = getMapValue(iMapX - 1, iMapY) == 0 ? ImageManager::loadImage("resource/tile/wall/wall_side_mid_left.png", true) 
			: ImageManager::loadImage("resource/tile/wall/wall_side_mid_right.png", true);
		image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			this->getTileWidth(), this->getTileHeight(),
			0x000000
		);
		break;
	case 5: //fountain
		fountain[0]->setX(iStartPositionScreenX);
		fountain[0]->setY(iStartPositionScreenY);
		fountain[1]->setX(iStartPositionScreenX);
		fountain[1]->setY(iStartPositionScreenY + this->getTileHeight());
		for (int i = 0; i < fountain.size(); i++)
		{
			fountain[i]->virtDoUpdate(pEngine->getModifiedTime());
			image = fountain[i]->getImage();
			image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight()
			);
		}
		break;
	case 6: //button
		button->setX(iStartPositionScreenX);
		button->setY(iStartPositionScreenY);
		button->virtDoUpdate(pEngine->getModifiedTime());
		image = button->getImage();
		image.renderImage(pEngine->getBackgroundSurface(), 0, 0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			this->getTileWidth(), this->getTileHeight()
		);
		if (getMapValue(iMapX, iMapY + 1) == 3) {
			image = ImageManager::loadImage("resource/tile/wall/wall_top_mid.png", true);
			image.renderImageWithMask(pEngine->getBackgroundSurface(), 0, 0,
				iStartPositionScreenX,
				iStartPositionScreenY,
				this->getTileWidth(), this->getTileHeight(),
				0x000000
			);
		}
		break;
	}
}
