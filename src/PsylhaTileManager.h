#pragma once
#include "TileManager.h"
#include "TileImage.h"

class PsylhaTileManager :
	public TileManager
{

public:
	PsylhaTileManager();
	~PsylhaTileManager();

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

	std::vector<TileImage*> getFountain() { return fountain; }
	ButtonTile* getButton() { return button; }
private:
	std::vector<TileImage*> fountain;
	ButtonTile* button;
};

