#pragma once
#include "PsylhaObject.h"
#include "TileImage.h"
#include "CollisionDetection.h"
class PsylhaEngine;

class PsylhaActor :
	public PsylhaObject
{
public:
	PsylhaActor(int xStart, int yStart, PsylhaEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: PsylhaObject(xStart, yStart, pEngine, strURL)
	{
		image = ImageManager::get()->getImagebyURL(strURL, true, true);
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2; 
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;

		iColLeftX = m_iCurrentScreenX;
		iColRightX = m_iCurrentScreenX + m_iDrawWidth;
		iColY = m_iCurrentScreenY + m_iDrawHeight;
		setVisible(bVisible);
	}
	~PsylhaActor() {}
	virtual void moveX(int i) {
		m_iCurrentScreenX += i;
		iColLeftX = m_iCurrentScreenX;
		iColRightX = m_iCurrentScreenX + m_iDrawWidth;
	}
	virtual void moveY(int i) {
		m_iCurrentScreenY += i;
		iColY = m_iCurrentScreenY + m_iDrawHeight;
	}
	void doCollisionDetection(bool left, bool right, bool up, bool down, PsylhaTileManager& tm)
	{
		int tempMapValue1 = tm.getMapValue(tm.getMapXForScreenX(iColLeftX), tm.getMapYForScreenY(iColY + 2)), 
			tempMapValue2 = tm.getMapValue(tm.getMapXForScreenX(iColLeftX), tm.getMapYForScreenY(iColY - 2));
		if (left && (tempMapValue1 != 1 && tempMapValue1 != 6)) {
			if (left && (tempMapValue2 != 1 && tempMapValue2 != 6)) {
				moveX(4);
				if (up && (tm.getMapValue(tm.getMapXForScreenX(iColLeftX + 2), tm.getMapYForScreenY(iColY - 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColLeftX + 2), tm.getMapYForScreenY(iColY - 2)) == 6)) {
					moveY(2);
					//std::cout << "leftup\n";
				}
				if (down && (tm.getMapValue(tm.getMapXForScreenX(iColLeftX + 2), tm.getMapYForScreenY(iColY + 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColLeftX + 2), tm.getMapYForScreenY(iColY + 2)) == 6)) {
					moveY(-2);
					//std::cout << "leftdown\n";
				}
			}
		}

		tempMapValue1 = tm.getMapValue(tm.getMapXForScreenX(iColRightX), tm.getMapYForScreenY(iColY + 2));
		tempMapValue2 = tm.getMapValue(tm.getMapXForScreenX(iColRightX), tm.getMapYForScreenY(iColY - 2));
		if (right && tempMapValue1 != 1 && tempMapValue1 != 6) {
			if (right && tempMapValue2 != 1 && tempMapValue2 != 6) {
				moveX(-4);
				if (up && (tm.getMapValue(tm.getMapXForScreenX(iColRightX - 2), tm.getMapYForScreenY(iColY - 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColRightX - 2), tm.getMapYForScreenY(iColY - 2)) == 6)) {
					moveY(2);
					//std::cout << "rightup\n";
				}
				if (down && (tm.getMapValue(tm.getMapXForScreenX(iColRightX - 2), tm.getMapYForScreenY(iColY + 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColRightX - 2), tm.getMapYForScreenY(iColY + 2)) == 6)) {
					moveY(-2);
					//std::cout << "rightdown\n";
				}
			}
		}

		tempMapValue1 = tm.getMapValue(tm.getMapXForScreenX(iColRightX), tm.getMapYForScreenY(iColY - 2));
		tempMapValue2 = tm.getMapValue(tm.getMapXForScreenX(iColLeftX), tm.getMapYForScreenY(iColY - 2));
		if (up && (tempMapValue1 != 1 && tempMapValue1 != 6 ||
			tempMapValue2 != 1 && tempMapValue2 != 6)) {
			moveY(4);
			if (left && (tm.getMapValue(tm.getMapXForScreenX(iColLeftX - 2), tm.getMapYForScreenY(iColY + 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColLeftX - 2), tm.getMapYForScreenY(iColY + 2)) == 6)) {
				moveX(2);
				//std::cout << "upleft\n";
			}
			if (right && (tm.getMapValue(tm.getMapXForScreenX(iColRightX + 2), tm.getMapYForScreenY(iColY + 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColRightX + 2), tm.getMapYForScreenY(iColY + 2)) == 6)) {
				moveX(-2);
				//std::cout << "upright\n";
			}
		}

		tempMapValue1 = tm.getMapValue(tm.getMapXForScreenX(iColRightX), tm.getMapYForScreenY(iColY + 2));
		tempMapValue2 = tm.getMapValue(tm.getMapXForScreenX(iColLeftX), tm.getMapYForScreenY(iColY + 2));
		if (down && (tempMapValue1 != 1 && tempMapValue1 != 6 ||
			tempMapValue2 != 1 && tempMapValue2 != 6)) {
			moveY(-4);
			if (left && (tm.getMapValue(tm.getMapXForScreenX(iColLeftX - 2), tm.getMapYForScreenY(iColY - 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColLeftX - 2), tm.getMapYForScreenY(iColY - 2)) == 6)) {
				moveX(2);
				//std::cout << "downleft\n";
			}
			if (right && (tm.getMapValue(tm.getMapXForScreenX(iColRightX + 2), tm.getMapYForScreenY(iColY - 2)) == 1 || tm.getMapValue(tm.getMapXForScreenX(iColRightX + 2), tm.getMapYForScreenY(iColY - 2)) == 6)) {
				moveX(-2);
				//std::cout << "downright\n";
			}
		}
	}
protected:
	int iColLeftX, iColRightX, iColY;
};

