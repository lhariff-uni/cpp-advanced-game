#pragma once
#include "PsylhaActor.h"
#include "MovementPosition.h"
#include "Player.h"

class Enemy :
	public PsylhaActor
{
public:
	Enemy(int xStart, int yStart, PsylhaEngine* pEngine, std::string strURL, Player* player)
		: PsylhaActor(xStart, yStart, pEngine, "resource/Enemy/" + strURL)
	{
		this->player = player;
		this->player->attach(this);
		folder = "resource/Enemy/";
		dir = false;
	}
	~Enemy() {
	}

	void update(const std::string& messageFromSubject)
	{
		msgFromPlayer = messageFromSubject;
	}
	void removeFromList()
	{
		player->detach(this);
	}
	void printInfo()
	{
		std::cout << msgFromPlayer << std::endl;
	}
protected:
	std::string folder;
	MovementPosition mov;
	bool dir;

	std::string msgFromPlayer;
	Player* player;
};

