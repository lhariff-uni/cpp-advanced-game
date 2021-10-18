#pragma once
#include "PsylhaObject.h"
#include "TextContainer.h"
class DisplayableText :
	public PsylhaObject
{
public:
	DisplayableText(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text, bool editable = false);
	DisplayableText(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text, int maxCharacters,bool editable = true);
	~DisplayableText();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	void virtKeyDown(int iKeyCode) override;
	void setText(std::string txt) { text->setText(txt); }
	std::string getText() { return text->getText(); }
private:
	TextContainer* text;
	bool editable;
	int maxChar;
};

