#pragma once

#include <vector>
#include <string>
#include <fstream>

class Map
{
private:
	std::vector<std::string> lvlList;
	int currentLvl;
	std::vector<std::string> lvlMap;
	int goalPlaces;
	int playerX, playerY;

	void readMap();
	void changeDashToSpace();
	bool moveBox(int boxX, int boxY, int dx, int dy);
	void playerFromBlank(int x, int y, int dx, int dy);
	void playerFromGoal(int x, int y, int dx, int dy);
	void boxFromBlank(int x, int y, int dx, int dy);
	void boxFromGoal(int x, int y, int dx, int dy);

public:
	Map();
	~Map();
	std::string drawMap();
	void nextMap();
	void prevMap();
	void resetMap();
	bool movePlayer(int dx, int dy);
	bool isWin();
};

