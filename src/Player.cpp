#include "header.h"
#include "Player.h"
#include "PsylhaEngine.h"
#include "Shot.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "DeathState.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

Player::Player(PsylhaEngine* pEngine, bool controllable, bool large)
	: PsylhaActor(pEngine->getWindowWidth()/2, pEngine->getWindowHeight()/2, pEngine, "resource/player/right/idle0.png")
{
	fp = "/idle";
	dir = true;
	this->controllable = controllable;
	this->large = large;
	limitButton = false;
	health = 5;
	skeletonCount = 0;
	demonCount = 0;
	//std::cout << std::to_string(large) << std::endl;
}
Player::Player(int xStart, int yStart, PsylhaEngine* pEngine, bool controllable, bool large)
	: PsylhaActor(xStart, yStart, pEngine, "resource/player/right/idle0.png")
{
	fp = "/idle";
	dir = true;
	this->controllable = controllable;
	this->large = large;
	limitButton = false;
	health = 5;
	skeletonCount = 0;
	demonCount = 0;
}


Player::~Player()
{
}

void Player::virtDraw()
{
	if (!isVisible()) {
		return;
	}
	int iTick = getEngine()->getModifiedTime() / 100;
	int iFrame = iTick % 30;
	if (fp.find("idle") == 1 || fp.find("run") == 1) {
		image = ImageManager::loadImage(folder + (large ? "large" : dir ? "right" : "left") + fp + std::to_string(iFrame % 4) + ".png", true);
	}
	else {
		image = ImageManager::loadImage(folder + (large ? "large" : dir ? "right" : "left") + fp + ".png", true);
	}
	image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
		m_iCurrentScreenX + m_iStartDrawPosX,
		m_iCurrentScreenY + m_iStartDrawPosY,
		image.getWidth(), image.getHeight() ,
		0x000000);
}

void Player::virtDoUpdate(int iCurrentTime)
{
	if (health < 0)
	{
		pEngine->setState(DBG_NEW DeathState(pEngine));
	}
	if (!isVisible() || getEngine()->isPaused())
		return;
	fp = "/idle";
	if (!controllable) {
		this->redrawRectangle();
		return;
	}

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
		if (!dynamic_cast<Enemy*>(pObject) && !dynamic_cast<EnemyShot*>(pObject))
			continue;

		if (CollisionDetection::checkRectangles(
			m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
			m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
			pObject->getXCentre() - pObject->getDrawWidth() / 2, pObject->getXCentre() + pObject->getDrawWidth() / 2,
			pObject->getYCentre() - pObject->getDrawHeight() / 2, pObject->getYCentre() + pObject->getDrawHeight() / 2
		))
		{
			if (!dynamic_cast<EnemyShot*>(pObject)) {
				if (dynamic_cast<Skeleton*>(pObject)) {
					addSkeletonCount();
				}
				else {
					addDemonCount();
				}

				pEngine->removeDisplayableObject(pObject);
				dynamic_cast<Enemy*>(pObject)->removeFromList();
				delete pObject;
			}
			else {
				pEngine->removeDisplayableObject(pObject);
				delete pObject;
			}
			fp = "/hit";
			health--;
		}
	}
	

	PsylhaTileManager& tm = pEngine->getTileManager();
	dir = getEngine()->getCurrentMouseX() > m_iCurrentScreenX + (m_iDrawWidth / 2);
	bool left = getEngine()->isKeyPressed(SDLK_a);
	bool right = getEngine()->isKeyPressed(SDLK_d);
	bool up = getEngine()->isKeyPressed(SDLK_w);
	bool down = getEngine()->isKeyPressed(SDLK_s);
	
	if (getEngine()->isKeyPressed(SDLK_SPACE)) {
		int iTick = getEngine()->getModifiedTime() / 10;
		int iFrame = iTick % 30;
		if (iFrame % 15 == 0) {
			pEngine->appendObjectToArray(
				DBG_NEW PlayerShot(pEngine, m_iCurrentScreenX + m_iDrawWidth / 2, m_iCurrentScreenY + m_iDrawHeight / 2, getEngine()->getCurrentMouseX(), getEngine()->getCurrentMouseY(), iCurrentTime)
			);
		}
	}
	if (left || right || 
		up || down) {
		fp = "/run";
		if (left) {
			moveX(-4);
		}
		if (right) {
			moveX(4);
		}
		if (up) {
			moveY(-4);
		}
		if (down) {
			moveY(4);
		}
	}
	doCollisionDetection(left, right, up, down, tm);
	int tempMapValue1 = tm.getMapValue(tm.getMapXForScreenX(iColRightX), tm.getMapYForScreenY(iColY));
	int tempMapValue2 = tm.getMapValue(tm.getMapXForScreenX(iColLeftX), tm.getMapYForScreenY(iColY));
	if ((tempMapValue1 == 6 || tempMapValue2 == 6) && !limitButton) {
		limitButton = true;
		tm.getButton()->setPath("resource/tile/button/true.png");
		tm.getButton()->setPlayerCollision(true);
	}
	else if ((tempMapValue1 == 6 || tempMapValue2 == 6) && limitButton) {

	}
	else {
		limitButton = false;
		tm.getButton()->setPath("resource/tile/button/false.png");
		tm.getButton()->setPlayerCollision(false);
	}
	createMessage(std::to_string(m_iCurrentScreenX + m_iDrawWidth / 2) + "_" + std::to_string(m_iCurrentScreenY + m_iDrawHeight / 2));
	this->redrawDisplay();
}

void Player::virtMouseDown(int iButton, int iX, int iY)
{

}

void Player::createMessage(std::string message)
{
	this->message = message;
	notify();
}
void Player::observerCount()
{
	std::cout << "observerCount = " << observerList.size() << std::endl;
}
void Player::attach(Enemy* enemy)
{
	observerList.push_back(enemy);
}
void Player::detach(Enemy* enemy)
{
	observerList.remove(enemy);
}
void Player::notify()
{
	std::list<Enemy*>::iterator itr = observerList.begin();

	while (itr != observerList.end()) {
		(*itr)->update(message);
		++itr;
	}
}