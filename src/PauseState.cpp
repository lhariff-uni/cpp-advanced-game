#include "header.h"
#include "PauseState.h"
#include "PsylhaEngine.h"
#include "DisplayableText.h"
#include "TextContainer.h"

#include "RunState.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

PauseState::PauseState(PsylhaEngine* pEngine, int skeletonCount, int demonCount)
	: State(pEngine)
{
	pEngine->pause();
	this->skeletonCount = skeletonCount;
	this->demonCount = demonCount;
	setupForeground();
}
PauseState::~PauseState()
{
}
/*
void PauseState::setupBackground()
{

}
*/
void PauseState::setupForeground()
{
	//pEngine->drawableObjectsChanged();
	pEngine->appendObjectToArray(DBG_NEW DisplayableText(pEngine->getWindowWidth() / 2 - 200, 200, pEngine, DBG_NEW TextContainer("game paused", 40, 0xfcba03)));
	pEngine->appendObjectToArray(DBG_NEW DisplayableText(pEngine->getWindowWidth() / 2 - 480, 250, pEngine, DBG_NEW TextContainer("press any key to unpause", 40, 0xffffff)));
}

void PauseState::keyUp(int iKeyCode)
{
	if (iKeyCode) {
		pEngine->drawableObjectsChanged();
		for (int i = 0; i < 2; i++) {
			DisplayableObject* pObject = pEngine->getDisplayableObject(pEngine->getContentCount() - 1);
			pEngine->removeDisplayableObject(pObject);
			delete pObject;
		}
		pEngine->setStateNoFlag(DBG_NEW RunState(pEngine, skeletonCount, demonCount));
	}
}