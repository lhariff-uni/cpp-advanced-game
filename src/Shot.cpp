#include "header.h"
#include "Shot.h"
#include "PsylhaEngine.h"

Shot::Shot(PsylhaEngine* pEngine, int iStartX, int iStartY, int iEndX, int iEndY, int time)
	: PsylhaObject(iStartX, iStartY, pEngine, 16, 16)
{
	int diffX = iEndX > iStartX ? iEndX - iStartX : iStartX - iEndX;
	int diffY = iEndY > iStartY ? iEndY - iStartY : iStartY - iEndY;
	mov.setup(
		iStartX,
		iStartY,
		iEndX,
		iEndY,
		time,
		time + diffX + diffY);
	setVisible(true);
}

Shot::~Shot() {
}

void Shot::virtDraw() {
	if (!isVisible())
		return;

	pEngine->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + 16, m_iCurrentScreenY + 16,
		0xffffff);
}
void EnemyShot::virtDraw() {
	if (!isVisible())
		return;

	pEngine->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + 16, m_iCurrentScreenY + 16,
		0xff5555);
}

void Shot::virtDoUpdate(int iCurrentTime) {
	if (!isVisible() || getEngine()->isPaused())
		return;
	if (mov.hasMovementFinished(iCurrentTime)) {
		pEngine->removeDisplayableObject(this);
		delete this;
	}
	mov.calculate(iCurrentTime);
	m_iCurrentScreenX = mov.getX();
	m_iCurrentScreenY = mov.getY();
}
