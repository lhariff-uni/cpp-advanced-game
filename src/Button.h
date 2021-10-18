#pragma once
#include "PsylhaObject.h"
#include "TextContainer.h"

#include "ScoreState.h"
#include "MenuState.h"
#include "RunState.h"
#include "ExitState.h"
#include "NameState.h"
#include "DisplayableText.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

class PsylhaEngine;
class Button :
	public PsylhaObject
{
public:
	Button(int xStart, int yStart, PsylhaEngine* pEngine, int w, int h, TextContainer* text);
	Button(int xStart, int yStart, PsylhaEngine* pEngine, TextContainer* text);
	~Button();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	bool getHover() { return hover; }
	void virtMouseUp(int iButton, int iX, int iY) override;
protected:
	bool hover;
	TextContainer* text;
};

class ScoreButton :
	public Button
{
public:
	using Button::Button;
	~ScoreButton() {}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->setState(DBG_NEW ScoreState(pEngine));
		}
	}
};

class SaveNameButton
	: public Button
{
public:
	using Button::Button;
	~SaveNameButton(){}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->setName(dynamic_cast<DisplayableText*>(pEngine->getDisplayableObject(0))->getText());
			pEngine->setState(DBG_NEW MenuState(pEngine));
		}
	}
};

class NameButton
	: public Button
{
public:
	using Button::Button;
	~NameButton() {}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->setState(DBG_NEW NameState(pEngine));
		}
	}
};

class MenuButton
	: public Button
{
public:
	using Button::Button;
	~MenuButton() {}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->setState(DBG_NEW MenuState(pEngine));
		}
	}
};

class PlayButton
	: public Button
{
public:
	using Button::Button;
	~PlayButton() {}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->resetPoints();
			pEngine->setState(DBG_NEW RunState(pEngine));
		}
	}
};

class ExitButton
	: public Button
{
	using Button::Button;
	~ExitButton() {}
	void virtMouseUp(int iButton, int iX, int iY) override
	{
		if (hover) {
			pEngine->setState(DBG_NEW ExitState(pEngine));
		}
	}
};
