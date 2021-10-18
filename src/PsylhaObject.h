#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "ImageManager.h"
#include "PsylhaEngine.h"
class PsylhaObject : public DisplayableObject
{
public:
	// Constructors
	PsylhaObject(PsylhaEngine* pEngine, int width, int height)
		: DisplayableObject(pEngine, width, height)
	{
		this->pEngine = pEngine;

	}
	PsylhaObject(int xStart, int yStart, PsylhaEngine* pEngine, int width, int height, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(xStart, yStart, pEngine, width, height, useTopLeftFor00)
	{
		this->pEngine = pEngine;
		m_iDrawWidth = width;
		m_iDrawHeight = height;
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(true);
	}

	PsylhaObject(PsylhaEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(pEngine, 100, 100, useTopLeftFor00),
		image(pEngine->loadImage(strURL, false/*don't keep it loaded*/))
	{
		this->pEngine = pEngine;
		this->m_iDrawWidth = image.getWidth();
		this->m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(true);
	}

	PsylhaObject(int xStart, int yStart, PsylhaEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(xStart, yStart, pEngine, 100, 100, useTopLeftFor00),
		image(ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/))
	{
		this->pEngine = pEngine;
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		// Offset within the drawing area to draw at - need to reset since width and height changed:
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(bVisible);
	}

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw() override
	{
		if (isVisible())
		{
			image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}

	void setImage(SimpleImage img) { image = img; }
protected:
	PsylhaEngine* pEngine;
	SimpleImage image;
};

