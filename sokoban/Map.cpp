#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	currentLvl = 0;
	goalPlaces = 0;
	playerX = -1;
	playerY = -1;
	lvlList = { "lvl1", "lvl2", "lvl3", "lvl4", "lvl5" };
	readMap();
}


Map::~Map()
{
}

std::string Map::drawMap(){
	std::string toReturn = "";
	toReturn.append(lvlList[currentLvl] + "\n");
	for (int i = 0; i < lvlMap.size(); i++){
		toReturn.append(lvlMap[i]+"\n");
	}
	return toReturn;
}

void Map::readMap(){
	lvlMap.clear();
	std::ifstream infile;
	infile.open(lvlList[currentLvl]+".txt");
	std::string readed = "";
	while (infile >> readed)
		lvlMap.push_back(readed);
	infile.close();
	changeDashToSpace();
}

void Map::changeDashToSpace(){
	for (int i = 0; i < lvlMap.size(); i++)
	for (int j = 0; j < lvlMap[i].length(); j++)
	if (lvlMap[i][j] == '_')
		lvlMap[i][j] = ' ';
	else if (lvlMap[i][j] == '@'){
		playerX = j; playerY = i;
	}
	else if (lvlMap[i][j] == '.')
		goalPlaces++;
}

void Map::nextMap(){
	currentLvl = ++currentLvl % lvlList.size();
	readMap();
}

void Map::prevMap(){
	currentLvl = --currentLvl;
	if (currentLvl < 0)
		currentLvl = lvlList.size() - 1;
	readMap();
}

void Map::resetMap(){
	readMap();
}

bool Map::movePlayer(int dx, int dy){
	if ( lvlMap[playerY + dy][playerX + dx]!= '#')
	if (moveBox(playerX + dx, playerY + dy, dx, dy)){
		playerFromBlank(playerX, playerY, dx, dy);
		playerFromGoal(playerX, playerY, dx, dy);
		playerX += dx;
		playerY += dy;
		return true;
	}
	return false;
}

bool Map::moveBox(int boxX, int boxY, int dx, int dy){
	if (lvlMap[boxY][boxX] == '$' || lvlMap[boxY][boxX] == '*'){
		if (lvlMap[boxY + dy][boxX + dx] == '$' || lvlMap[boxY + dy][boxX + dx] == '#' || lvlMap[boxY + dy][boxX + dx] == '*'){
			return false;
		}
		boxFromBlank(boxX, boxY, dx, dy);
		boxFromGoal(boxX, boxY, dx, dy);
	}
	return true;
}

void Map::boxFromBlank(int x, int y, int dx, int dy){
	if (lvlMap[y][x] == '$'){
		lvlMap[y][x] = ' ';
		if (lvlMap[y + dy][x + dx] == '.'){
			lvlMap[y + dy][x + dx] = '*';
			goalPlaces--;
		}else
			lvlMap[y + dy][x + dx] = '$';
	}
}

void Map::boxFromGoal(int x, int y, int dx, int dy){
	if (lvlMap[y][x] == '*'){
		lvlMap[y][x] = '.';
		if (lvlMap[y + dy][x + dx] == '.'){
			lvlMap[y + dy][x + dx] = '*';
		}else{
			lvlMap[y + dy][x + dx] = '$';
			goalPlaces++;
		}			
	}
}

void Map::playerFromBlank(int x, int y, int dx, int dy){
	if (lvlMap[y][x] == '@'){
		lvlMap[y][x] = ' ';
		if (lvlMap[y + dy][x + dx] == '.')
			lvlMap[y + dy][x + dx] = '+';
		else
			lvlMap[y + dy][x + dx] = '@';			
	}
}

void Map::playerFromGoal(int x, int y, int dx, int dy){
	if (lvlMap[y][x] == '+'){
		lvlMap[y][x] = '.';
		if (lvlMap[y + dy][x + dx] == '.')
			lvlMap[y + dy][x + dx] = '+';
		else
			lvlMap[y + dy][x + dx] = '@';
	}
}

bool Map::isWin(){
	return goalPlaces == 0 ? true : false;
}