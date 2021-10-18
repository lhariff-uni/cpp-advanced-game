#pragma once
#include "PsylhaObject.h"
#include "MovementPosition.h"

class PsylhaEngine;

class Shot :
	public PsylhaObject
{
public:
	Shot(PsylhaEngine* pEngine, int, int, int, int, int);
	~Shot();

	virtual void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
protected:
	MovementPosition mov;
};

class PlayerShot :
	public Shot
{
public:
	using Shot::Shot;
	~PlayerShot() {}
};

class EnemyShot :
	public Shot
{
public:
	using Shot::Shot;
	~EnemyShot() {}
	void virtDraw() override;
};
