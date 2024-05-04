#pragma once
#include "ListOfShapes.h"
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <fstream>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"


class GameInterface
{
	int score;	
	void printList(ListOfShapes&);
	void printListToFile(ofstream &, ListOfShapes &) ;
public:
	GameInterface() {
		score = 0;
	}
	void printShape(Shape&);
	int getScore();
	void setScore(int Score);
	void helloInterface();
	void menuInterface();
	void firstLevelInterface();
	void storeGame(int score, ListOfShapes& list, const Shape& current, const Shape& next);
	void loadGame();
	void storeHeighScore(string username);
};

