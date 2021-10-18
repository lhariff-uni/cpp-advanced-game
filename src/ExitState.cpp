#include "header.h"
#include "ExitState.h"
#include "Score.h"
#include "PsylhaEngine.h"
#include <fstream>
#include <iostream>
#include <vector>

ExitState::ExitState(PsylhaEngine* pEngine)
	: State(pEngine)
{
	saveHighScore();
	saveName();
}
ExitState::~ExitState()
{

}
void ExitState::saveHighScore()
{
	std::fstream file;
	std::string line;
	std::vector<std::shared_ptr<Score>> vecScore = pEngine->getScore();
	file.open("data/highscore.txt", std::ios::out, std::ofstream::trunc);
	for (int i = 0; i < vecScore.size(); i++)
	{
		file << vecScore[i]->getName() << vecScore[i]->getScore() << "\n";
	}
	file.close();
}
void ExitState::saveName()
{
	std::fstream file;
	std::string line;
	file.open("data/name.txt", std::ios::out, std::ofstream::trunc);
	file << pEngine->getName() << "\n";
	//std::cout << pEngine->getName() << "\n";
	file.close();
}
