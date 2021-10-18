#include "header.h"
#include "Skeleton.h"
#include "Shot.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

Skeleton::Skeleton(int xStart, int yStart, PsylhaEngine* pEngine, Player* player)
	: Enemy(xStart, yStart, pEngine, "/skeleton/left/idle0.png", player)
{
	folder += "skeleton/";
	fp = "/idle";
	mov.setup(
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		pEngine->getModifiedTime(),
		pEngine->getModifiedTime() + 1000);
}
Skeleton::~Skeleton()
{

}

void Skeleton::virtDraw() 
{
	if (!isVisible()) {
		return;
	}
	int iTick = getEngine()->getModifiedTime() / 100;
	int iFrame = iTick % 30;
	if (fp.find("idle") == 1 || fp.find("run") == 1) {
		image = ImageManager::loadImage(folder + (dir ? "right" : "left") + fp + std::to_string(iFrame % 4) + ".png", true);
	}
	m_iDrawHeight = image.getHeight();
	m_iDrawWidth = image.getWidth();
	image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
		m_iCurrentScreenX + m_iStartDrawPosX,
		m_iCurrentScreenY + m_iStartDrawPosY,
		m_iDrawWidth, m_iDrawHeight,
		0x000000);
}
void Skeleton::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible() || getEngine()->isPaused())
		return;
	
	DisplayableObject* pObject;
	for (int iObjectId = 0;
		(pObject = pEngine->getDisplayableObject(iObjectId)
			) != NULL;
		iObjectId++)
	{
		if (pObject == this)
			continue;
		if (pObject == nullptr)
			continue;
		if (!dynamic_cast<PlayerShot*>(pObject))
			continue;

		if (CollisionDetection::checkRectangles(
			m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
			m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
			pObject->getXCentre() - pObject->getDrawWidth()/2, pObject->getXCentre() + pObject->getDrawWidth() / 2,
			pObject->getYCentre() - pObject->getDrawHeight() / 2, pObject->getYCentre() + pObject->getDrawHeight() / 2
		))
		{
			pEngine->removeDisplayableObject(pObject);
			delete pObject;

			pEngine->addPoints(5);
			player->addSkeletonCount();
			pEngine->removeDisplayableObject(this);
			removeFromList();
			delete this;
			return;
		}
	}
	
	if (mov.hasMovementFinished(iCurrentTime)) 
	{
		fp = "/run";
		int iEndX = std::atoi((msgFromPlayer.substr(0, msgFromPlayer.find("_"))).c_str());
		int iEndY = std::atoi((msgFromPlayer.substr(msgFromPlayer.find("_") + 1, msgFromPlayer.length() - msgFromPlayer.find("_"))).c_str());
		int diffX = iEndX > m_iCurrentScreenX ? iEndX - m_iCurrentScreenX : m_iCurrentScreenX - iEndX;
		int diffY = iEndY > m_iCurrentScreenY ? iEndY - m_iCurrentScreenY : m_iCurrentScreenY - iEndY;
		mov.setup(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			iEndX,
			iEndY,
			iCurrentTime,
			iCurrentTime + (diffX + diffY) * 3);
	}
	mov.calculate(iCurrentTime); 
	bool left = m_iCurrentScreenX > mov.getX(),
		right = m_iCurrentScreenX < mov.getX(),
		up = m_iCurrentScreenY > mov.getY(),
		down = m_iCurrentScreenY < mov.getY();
	dir = mov.getX() - m_iCurrentScreenX > 1;
	moveX(mov.getX() - m_iCurrentScreenX > 1 ? 4 : mov.getX() - m_iCurrentScreenX < -1 ? -4 : 0);
	moveY(mov.getY() - m_iCurrentScreenY > 1 ? 4 : mov.getY() - m_iCurrentScreenY < -1 ? -4 : 0);
	this->doCollisionDetection(left,right,up,down,pEngine->getTileManager());
}