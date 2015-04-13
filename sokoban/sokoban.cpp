// sokoban.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

void prepareConsoleView(){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	// max chars is 45
	MoveWindow(console, r.left + 100, r.top , 950, 600, true);
}

std::string showLegend(){
	std::string toReturn = "";
	toReturn.append("=== MAP LEGEND ===\n");
	toReturn.append("@ - Player\n");
	toReturn.append("+ - Player on goal square\n");
	toReturn.append(". - Goal Square\n");
	toReturn.append("$ - Box\n");
	toReturn.append("* - Box on goal square\n");
	toReturn.append("# - Wall\n");
	toReturn.append(":space: - Floor\n\n");
	toReturn.append("=== KEY LEGEND ===\n");
	toReturn.append("w - up\n");
	toReturn.append("s - down\n");
	toReturn.append("a - left\n");
	toReturn.append("d - right\n");
	return toReturn;
}

std::string showMenu(){
	std::string toReturn = "";
	toReturn.append("=== GAME FUNC LEGEND ===\n");
	toReturn.append("h - help\n");
	toReturn.append("n - next map\n");
	toReturn.append("p - prev map\n");
	toReturn.append("r - restart current map\n");
	toReturn.append("ESC - turnoff the game\n");
	return toReturn;
}

int _tmain(int argc, _TCHAR* argv[])
{

	prepareConsoleView();

	HANDLE current = GetStdHandle(STD_OUTPUT_HANDLE);

	HANDLE buffer = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
		);

	std::cout << showLegend();
	std::cout << std::endl;
	std::cout << showMenu();

	std::cout << std::endl << "Press any key to continue..." << std::endl;
	_getch();

	Map* mapa = new Map();

	bool play = true;
	bool help = false;
	bool first = true;
	unsigned long written = 0;
	std::string draw = "";
	
	int moves = 0;

	while (play){

		draw = "";

		if (_kbhit()){
			int key = _getch();
			if (key == 97 || key == 75){
				// left
				if(mapa->movePlayer(-1, 0))
				moves++;
			}else if (key == 100 || key == 77){
				// right
				if(mapa->movePlayer(1, 0))
				moves++;
			}else if (key == 119 || key == 72){
				// up
				if(mapa->movePlayer(0, -1))
				moves++;
			}else if (key == 115 || key == 80){
				// down
				if(mapa->movePlayer(0, 1))
				moves++;
			}else if (key == 104){
				// help
				help = true;
			}else if (key == 110){
				// next map
				mapa->nextMap();
				moves = 0;
			}else if (key == 112){
				// prev map
				mapa->prevMap();
				moves = 0;
			}else if (key == 114){
				// reset map
				mapa->resetMap();
				moves = 0;
			}else if (key == 27){
				// ESC to quite the game
				break;
			}else {
				help = false;
				system("cls");
			}
		}

		if (help){
			draw = showLegend();
		}else{
			draw.append(mapa->drawMap());
			draw.append("Moves: " +  std::to_string(moves) + "\n");
		}

		const char* nap = draw.c_str();
		if (first){
			WriteConsoleA(current, nap, strlen(nap), &written, NULL);
			system("cls");
			SetConsoleActiveScreenBuffer(current);
			first != first;
		}
		else{
			WriteConsoleA(buffer, nap, strlen(nap), &written, NULL);
			system("cls");
			SetConsoleActiveScreenBuffer(buffer);
			first != first;
		}

		if (mapa->isWin()){
			mapa->nextMap();
			moves = 0;
		}		

	}

	std::cout << "==============================================" << std::endl;
	std::cout << "================= END GAME ===================" << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << std::endl << "	U done " + std::to_string(moves) + " moves on last map." << std::endl << std::endl;

	system("pause");

	delete(mapa);

	return 0;
}
