#pragma once
#include <string>
class Score
{
public:
	Score(std::string name, std::string score)
	{
		this->name = name;
		this->score = score;
	}
	~Score()
	{

	}
	std::string getName() { return name; }
	std::string getScore() { return score; }
private:
	std::string name;
	std::string score;
};

