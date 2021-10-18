#include "header.h"
#include "DisplayableText.h"
#include "PsylhaEngine.h"

DisplayableText::DisplayableText(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text, bool editable)
	: PsylhaObject(xStart, yStart, pEngine, text->getWidth(), text->getHeight())
{
	this->text = text;
	this->editable = editable;
	maxChar = 0;
}
DisplayableText::DisplayableText(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text, int maxCharacters, bool editable)
	: PsylhaObject(xStart, yStart, pEngine, text->getWidth(), text->getHeight())
{
	this->editable = editable;
	maxChar = maxCharacters;
	this->text = text;
	this->text->setText(text->getText().substr(0, maxChar));
}
DisplayableText::~DisplayableText()
{
	delete text;
}

void DisplayableText::virtDraw()
{
	m_iDrawWidth = text->getWidth();
	m_iDrawHeight = text->getHeight();
	if (!text->getText().empty()) {
		pEngine->drawForegroundString(
			m_iCurrentScreenX, m_iCurrentScreenY,
			text->getText().c_str(), text->getColour(),
			pEngine->getFont("Tecmo Bowl.ttf", text->getSize())
		);
	}
}
void DisplayableText::virtDoUpdate(int iCurrentTime)
{
	this->redrawRectangle();
}
void DisplayableText::virtKeyDown(int iKeyCode)
{
	if (!editable)
		return;

	std::string str = text->getText();
	if (iKeyCode == SDLK_BACKSPACE) {
		if (str.length() <= 1) {
			str = "";
		}
		else {
			str.pop_back();
		}
	}
	else if (maxChar && str.length() >= maxChar) {
		return;
	}
	else if (iKeyCode == SDLK_SPACE) {
		str.push_back(iKeyCode);
	}
	else if (iKeyCode > 64 && iKeyCode < 91) {
		str.push_back(iKeyCode);
	}
	else if (iKeyCode > 96 && iKeyCode < 123) {
		str.push_back(iKeyCode);
	}
	text->setText(str);
	this->redrawRectangle();
}