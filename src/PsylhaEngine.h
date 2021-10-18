#pragma once
#include "BaseEngine.h"
#include "PsylhaTileManager.h"
#include "State.h"
#include "Score.h"

class PsylhaEngine :
	public BaseEngine
{
public:
	PsylhaEngine();
	~PsylhaEngine();
	int virtInitialise() override;
	void virtSetupBackgroundBuffer() override;
	int virtInitialiseObjects() override;
	void virtKeyUp(int iKeyCode) override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	PsylhaTileManager& getTileManager() { return tm; }

	std::string getName() { return name; }
	std::vector<std::shared_ptr<Score>> getScore() { return vecScore; }
	void setScore(std::vector<std::shared_ptr<Score>> scr) { vecScore = scr; }
	void setName(std::string name) { this->name = name; }
	void setState(State* s) { 
		state.reset(s);
		stateChanged = true;
	}
	void setStateNoFlag(State* s) {
		state.reset(s);
	}
	void resetPoints() { points = 0; }
	void addPoints(int point) { points += point; }
	int getPoints() { return points; }
	

	void virtMainLoopStartIteration() override;
	void virtMainLoopPostUpdate() override;
private:
	void loadScores();
	void loadName();
	PsylhaTileManager tm;
	std::unique_ptr<State> state;
	std::string name;
	int points;
	std::vector<std::shared_ptr<Score>> vecScore;

	bool stateChanged;
};

