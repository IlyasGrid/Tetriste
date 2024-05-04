#include "GameInterface.h" // Assuming GameInterface.h contains the class declaration
#include <iostream> // For cout
#include <fstream> // For file operations

using namespace std;

// Function to clear the console screen
void clearScreen() {
	system("cls");
}

// Function to set the cursor position
void setCursorPosition(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameInterface::printShape(Shape& shape) {

	if (shape.node->getColor() == "red")
		cout << ANSI_COLOR_RED;
	else if (shape.node->getColor() == "green")
		cout << ANSI_COLOR_GREEN;
	else if (shape.node->getColor() == "blue")
		cout << ANSI_COLOR_BLUE;
	else if (shape.node->getColor() == "yellow")
		cout << ANSI_COLOR_YELLOW;
	else
		cout << ANSI_COLOR_RESET;
	cout << " " << shape.node->getName() << ANSI_COLOR_RESET;

	//cout << " " << shape.node->getName() ;

}

void GameInterface::printList(ListOfShapes& list) {

	Shape* current = list.getStart();
	while (current != nullptr) {
		this->printShape(*current);
		current = current->next;
	}

}

void GameInterface::printListToFile(std::ofstream& file, ListOfShapes& list)  {
	// Get the start of the list
	Shape* current = list.getStart();
	file << "List: " << std::endl;

	// Traverse the list and print each shape's details to the file
	while (current != nullptr) {
		file << "	Shape: " << std::endl;
		file << "		Color: " << current->node->getColor() << std::endl;
		file << "		Name: " << current->node->getName() << std::endl;
		current = current->next;
	}
}


// Getter for score
int GameInterface::getScore() {
	return score;
}

// Setter for score
void GameInterface::setScore(int newScore) {
	score = newScore;
}

// Method to greet the user
void GameInterface::helloInterface() {
	cout << "Welcome to the Tetris Game !!!!" << endl;
	cout << "Press Enter to continue...";
	cin.get();
	menuInterface();
}

// Method to display the menu
void GameInterface::menuInterface() {
	bool validChoice = false;

	do {
		clearScreen();
		setCursorPosition(2, 2);
		cout << "Menu:  " << endl;
		cout << "           1. Start Game " << endl;
		cout << "           2. Load Game " << endl;
		cout << "           3. Store Game " << endl;
		cout << "           4. View High Scores " << endl;
		cout << "           5. Exit " << endl;


		int choice = 0;
		cin >> choice;

		switch (choice) {
		case 1:
			firstLevelInterface();
			validChoice = true;
			break;
		case 2:
			cout << "Load Game" << endl;
			validChoice = true;
			break;
		case 3:
			cout << "Store Game" << endl;
			validChoice = true;
			break;
		case 4:
			cout << "View High Scores" << endl;
			validChoice = true;
			break;
		case 5:
			cout << "Exiting..." << endl;
			validChoice = true;
			break;
		default:
			cout << "Invalid choice. Please select again." << endl;
			break;
		}

		// Pause to see the output
		cout << "Press Enter to continue...";
		cin.ignore();
		cin.get();

	} while (validChoice);

}



//used in Level

void chooseColorForShift(ListOfShapes& shapeList) {
	cout << "	choose : \n		1-red\n		2-blue\n		3-green\n		4-yellow" << endl;

	char choise = getchar();
	std::cin.ignore();

	switch (choise)
	{
	case '1':

		shapeList.shiftShapesWithSameColor("red");
		break;
	case '2':
		shapeList.shiftShapesWithSameColor("blue");
		break;
	case '3':
		shapeList.shiftShapesWithSameColor("green");
		break;
	case '4':
		shapeList.shiftShapesWithSameColor("yellow");
		break;
	default:
		chooseColorForShift(shapeList);
		break;
	}
}

 void chooseNameForShift(ListOfShapes& shapeList) {
	cout << "	choose : \n		1-SQUARE\n		2-TRIANGLE\n		3-CIRCLE\n		4-LOSANGE" << endl;
	char choise = getchar();
	std::cin.ignore();
	switch (choise)
	{
	case '1':
		shapeList.shiftShapesWithSameName("SQUARE");
		break;
	case '2':
		shapeList.shiftShapesWithSameName("TRIANGLE");
		break;
	case '3':
		shapeList.shiftShapesWithSameName("CIRCLE");
		break;
	case '4':
		shapeList.shiftShapesWithSameName("LOSANGE");
		break;
	default:
		chooseNameForShift(shapeList);
		break;
	}
}


// Methode to dipaly the first level
void GameInterface::firstLevelInterface() {

	ListOfShapes list;
	Shape* nextShape = new Shape();
	Shape* currentShape = new Shape();
	bool newShapeNeeded = true;



	while (list.getShapeCount() < 15 ) {

		int userChoice;

		clearScreen();

		setCursorPosition(2, 2);
		cout << "Command:  " << endl;
		cout << "           a : insert in the start " << endl;
		cout << "           d : insert in the end " << endl;
		cout << "           w : to choose the wanted color shift " << endl;
		cout << "           s : to choose the wanted shape shift " << endl;
		cout << "           k : to store game and exit " << endl;

		setCursorPosition(2, 9);
		cout << "---------   Score: " << score << "    -------------";

		setCursorPosition(50, 10);
		cout << "Next Shape:  ";
		if (nextShape != nullptr)
			this->printShape(*nextShape);

		setCursorPosition(2, 10);
		cout << "Current Shape: ";
		if (currentShape != nullptr)
			this->printShape(*currentShape);

		// Display list of shapes
		setCursorPosition(2, 15);
		cout << "Shape List: (" << list.getShapeCount() << ") " << endl;
		setCursorPosition(2, 17);
		this->printList(list);

		// Prompt the user to choose the position
		setCursorPosition(2, 20);
		userChoice = _getch();
		
		userChoice = tolower(userChoice);

		switch (userChoice) {

		case 'a':
			
			list.appendShape(currentShape, 's');
			newShapeNeeded = true;
			break;
		case 'd':
			list.appendShape(currentShape, 'e');
			newShapeNeeded = true;
			break;
		case 's':

			chooseColorForShift(list);
			newShapeNeeded = false;
			break;
		case 'w':
			chooseNameForShift(list);
			newShapeNeeded = false;
			break;
		case 'k':
			newShapeNeeded = false;
			storeGame(score,list,*currentShape, *nextShape);
			list.setShapeCount(20);
			break;
		default:
			newShapeNeeded = false;
			break;
		}

		list.checkShapes(&score);

		if (newShapeNeeded) {
			currentShape = nextShape;
			nextShape = new Shape();
		}
	}
}

// Method to store the game state
void GameInterface::storeGame(int score, ListOfShapes& list, const Shape& current, const Shape& next) {
	// Open a file for writing
	std::time_t currentTime = std::time(nullptr);
	std::string fileName = "game_data.txt";
	std::ofstream file(fileName);

	// Write the score to the file
	file << "Score: " << score << std::endl;

	// Write the list of shapes to the file
	file << "List of Shapes:" << std::endl;
	// Assuming ListOfShapes has a print function
	this->printListToFile(file,list);

	// Write the details of the current shape to the file
	file << "Current Shape:" << std::endl;
	file << "	Color: " << current.node->getColor() << std::endl;
	file << "	Name: " << current.node->getName() << std::endl;

	// Write the details of the next shape to the file
	file << "Next Shape:" << std::endl;
	file << "	Color: " << next.node->getColor() << std::endl;
	file << "	Name: " << next.node->getName() << std::endl;

	// Close the file
	file.close();
}

// Method to load a previously saved game
void GameInterface::loadGame() {
	// Implement loading game logic here
}

// Method to store the high score along with the username
void GameInterface::storeHeighScore(string username) {
	// Implement storing high score logic here
}

