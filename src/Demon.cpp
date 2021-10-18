#include "header.h"
#include "Demon.h"
#include "Shot.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

Demon::Demon(int xStart, int yStart, PsylhaEngine* pEngine, Player* player)
	: Enemy(xStart, yStart, pEngine, "/demon/left/idle0.png", player)
{
	folder += "demon/";
	fp = "/idle";
	
	mov.setup(
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		pEngine->getModifiedTime(),
		pEngine->getModifiedTime() + 1500);
}
Demon::~Demon()
{

}

void Demon::virtDraw()
{
	if (!isVisible()) {
		return;
	}
	pEngine->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight - 5,
		m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight + 5,
		0x121212
	);
	int iTick = getEngine()->getModifiedTime() / 100;
	int iFrame = iTick % 30;
	if (fp.find("idle") == 1) {
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
void Demon::virtDoUpdate(int iCurrentTime)
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
			pObject->getXCentre() - pObject->getDrawWidth() / 2, pObject->getXCentre() + pObject->getDrawWidth() / 2,
			pObject->getYCentre() - pObject->getDrawHeight() / 2, pObject->getYCentre() + pObject->getDrawHeight() / 2
		))
		{
			pEngine->removeDisplayableObject(pObject);
			delete pObject;

			pEngine->addPoints(15);
			player->addDemonCount();
			pEngine->removeDisplayableObject(this);
			removeFromList();
			delete this;
			return;
		}
	}
	if (mov.hasMovementFinished(iCurrentTime))
	{
		
		int iEndX = std::atoi((msgFromPlayer.substr(0, msgFromPlayer.find("_"))).c_str());
		int iEndY = std::atoi((msgFromPlayer.substr(msgFromPlayer.find("_") + 1, msgFromPlayer.length() - msgFromPlayer.find("_"))).c_str());
		int iTick = pEngine->getModifiedTime()/10;
		dir = iEndX - m_iCurrentScreenX > 1;
		if (iTick % 80 == 20) {
			pEngine->appendObjectToArray(
				DBG_NEW EnemyShot(pEngine, m_iCurrentScreenX + m_iDrawWidth / 2, m_iCurrentScreenY + m_iDrawHeight / 2, iEndX, iEndY, iCurrentTime)
			);
		}
	}
}