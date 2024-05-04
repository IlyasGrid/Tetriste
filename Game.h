#pragma once
#include "raylib.h"
class Game
{
	int score;

public:
	Game(); // here where all needed initialization
	void menu(); // display the menu interface where the user can choose to (start a new game , continue from last game , diplay heighscore table  , diplay how to play interface)
	void level(); // display the game interface where it have a score in left corner ,  name of the game in middle top , then just under it two blocks within the first have the current shape , the other has the next shape , then under it we have a recatngle likw 80% of the width )
	void heighscore(); // display an interface with names with thier score ;
	void howToplay();

};

