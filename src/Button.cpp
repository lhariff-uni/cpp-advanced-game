#include "header.h"
#include "Button.h"
#include "PsylhaEngine.h"
#include "State.h"
const int PADDING = 20;

Button::Button(int xStart, int yStart, PsylhaEngine* pEngine, int w, int h, TextContainer* text)
	: PsylhaObject(xStart, yStart, pEngine, w, h, true)
{
	hover = false;
	this->text = text;
	if (w < text->getWidth()) {
		m_iDrawWidth = text->getWidth() + PADDING;
	}
	if (h < text->getHeight()) {
		m_iDrawHeight = text->getHeight() + PADDING;
	}
}
Button::Button(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text)
	: PsylhaObject(xStart, yStart, pEngine, text->getWidth() + PADDING, text->getHeight() + PADDING)
{
	hover = false;
	this->text = text;
}
Button::~Button() {
	delete text;
}

void Button::virtDraw() 
{
	pEngine->drawForegroundString(
		m_iCurrentScreenX + (m_iDrawWidth / 2) - (hover ? (text->getWidth() * 4 / 3) / 2 : text->getWidth() / 2),
		m_iCurrentScreenY + (m_iDrawHeight / 2) - (hover ? (text->getHeight() * 4 / 3) / 2 : text->getHeight() / 2),
		text->getText().c_str(), hover ? text->getColour() : text->getColour() - 0x999999,
		pEngine->getFont("Tecmo Bowl.ttf", hover ? text->getSize() * 4/3 : text->getSize())
	);
}
void Button::virtDoUpdate(int iCurrentTime)
{
	if (iCurrentTime < 10) {
		hover = false;
	}
	hover =
		pEngine->getCurrentMouseX() >= m_iCurrentScreenX &&
		pEngine->getCurrentMouseX() <= m_iCurrentScreenX + m_iDrawWidth &&
		pEngine->getCurrentMouseY() >= m_iCurrentScreenY &&
		pEngine->getCurrentMouseY() <= m_iCurrentScreenY + m_iDrawHeight;
	this->redrawDisplay();
}

void Button::virtMouseUp(int iButton, int iX, int iY)
{
	if (hover) {
		std::cout << "basebutton press" << std::endl;
	}
}