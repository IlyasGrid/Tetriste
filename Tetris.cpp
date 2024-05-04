//
//#include <iostream>
//#include "GameInterface.h"
//using namespace std;
//
//int main()
//{
//    GameInterface game;
//
//    game.helloInterface();
//}


#include "raylib.h"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "ListOfShapes.h"
#include <algorithm> 



class Game {
	int screenWidth;
	int screenHeight;
	int score;
	bool gameRunning;

public:
	Game() {
		screenWidth = 1000;
		screenHeight = 600;
		score = 0;
		gameRunning = true;
		InitWindow(screenWidth, screenHeight, "Tetris Game");
	}
	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
	bool isGameRunning() { return gameRunning; }
	void drawTable();
	void drawMenu();
	void goodbye();
	void drawGameScreen(ListOfShapes* shapelist = nullptr, Shape* currentShape = nullptr, Shape* nextShape = nullptr);
	void storeGame(int score);

};

Color getRealColor(Shape* shape)
{
	if (shape->node->color == "red")
		return RED;
	if (shape->node->color == "blue")
		return BLUE;
	if (shape->node->color == "yellow")
		return YELLOW;
	if (shape->node->color == "green")
		return GREEN;
}

void DrawSquareFromCoords(int x, int y, Color color) {
	DrawRectangle(x - 30, y - 30, 60, 60, color);
}

void DrawTriangleFromCoords(int x, int y, Color color)
{
	Vector2 v1 = { x , y - 30 };     // First vertex
	Vector2 v2 = { x - 30, y + 30 }; // Second vertex
	Vector2 v3 = { x + 30, y + 30 }; // Third vertex
	DrawTriangle(v1, v2, v3, color);
}

void DrawLozengeFromCoords(int x, int y, Color color)
{
	Vector2 v1 = { x , y - 30 };     // First vertex
	Vector2 v2 = { x - 30, y }; // Second vertex
	Vector2 v3 = { x , y + 30 }; // Third vertex
	Vector2 v4 = { x + 30, y };

	DrawTriangle(v1, v2, v3, color);
	DrawTriangle(v3, v4, v1, color);
}

void DrawCircleFromCoords(int x, int y, Color color) {
	DrawCircle(x, y, 30, color);
}

void DrawRoundedRectangle(int x, int y, int width, int height, int radius, Color color)
{
	// Draw main rectangle
	DrawRectangle(x + radius, y, width - radius * 2, height, color);
	DrawRectangle(x, y + radius, width, height - radius * 2, color);

	// Draw rounded corners
	DrawCircle(x + radius, y + radius, radius, color);
	DrawCircle(x + width - radius, y + radius, radius, color);
	DrawCircle(x + radius, y + height - radius, radius, color);
	DrawCircle(x + width - radius, y + height - radius, radius, color);

	// Fill in the gaps between the circles and the rectangles
	DrawRectangle(x + radius, y - 1, width - radius * 2, radius, color);
	DrawRectangle(x - 1, y + radius, radius, height - radius * 2, color);
	DrawRectangle(x + width - radius, y + radius, radius, height - radius * 2, color);
	DrawRectangle(x + radius, y + height - radius, width - radius * 2, radius, color);
}

void drawShape(Shape* shape, int x, int y) {
	if (shape->node->name == "TRIANGLE")
		DrawTriangleFromCoords(x, y, getRealColor(shape));
	if (shape->node->name == "LOSANGE")
		DrawLozengeFromCoords(x, y, getRealColor(shape));
	if (shape->node->name == "CIRCLE")
		DrawCircleFromCoords(x, y, getRealColor(shape));
	if (shape->node->name == "SQUARE")
		DrawSquareFromCoords(x, y, getRealColor(shape));
}




void Game::drawMenu() {

	Texture2D backgroundImage = LoadTexture("./img/menu.png");

	while (!WindowShouldClose()) {


		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(backgroundImage, 0, 0, WHITE);
		Font titleFont = GetFontDefault();
		int titleFontSize = 80;
		Vector2 titleTextSize = MeasureTextEx(titleFont, "Tetris Game", titleFontSize, 0);

		int centerX = GetScreenWidth() / 2 ;
		int centerY = GetScreenHeight() / 2 + 25;

		DrawText("Tetriste", centerX - titleTextSize.x / 2, 170, titleFontSize, WHITE);

		// Draw menu options
		const char* menuOptions[] = { "1. Start Game", "2. Load Game", "3. View High Scores", "4. Exit" };
		int menuFontSize = 25;
		int menuSpacing = 50; // Spacing between menu options
		for (int i = 0; i < 4; i++) {
			Vector2 menuTextSize = MeasureTextEx(titleFont, menuOptions[i], menuFontSize, 0);
			int menuY = centerY + i * menuSpacing;
			DrawText(menuOptions[i], centerX - menuTextSize.x / 2 , menuY, menuFontSize, RAYWHITE);
		}

		EndDrawing();

		if (IsKeyPressed(KEY_ONE)) {
			int score = 0;
			drawGameScreen();
			break;
		}
		else if (IsKeyPressed(KEY_TWO)) {
			ListOfShapes* shapelist = new ListOfShapes();
			Shape* currentShape = new Shape();
			Shape* nextShape = new Shape();
			shapelist->appendShape(new Shape(), 's');
			shapelist->appendShape(new Shape(), 's');
			shapelist->appendShape(new Shape(), 's');
			shapelist->appendShape(new Shape(), 's');
			shapelist->appendShape(new Shape(), 's');
			shapelist->appendShape(new Shape(), 's');
			drawGameScreen(shapelist, currentShape, nextShape);
		}
		else if (IsKeyPressed(KEY_THREE)) {
			drawTable();
			break;
		}
		else if (IsKeyPressed(KEY_FOUR)) {
			goodbye();
			break;

		}
	}
}

void Game::drawTable() {

	std::vector<std::pair<std::string, int>> data;
	std::string fileName = "game_data.txt";
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		// Split the line by the colon
		size_t colonPos = line.find(':');
		if (colonPos == std::string::npos) {
			std::cerr << "Invalid format in file: " << fileName << std::endl;
			continue; // Skip this line
		}

		// Extract the name and score
		std::string name = line.substr(0, colonPos);
		std::string scoreStr = line.substr(colonPos + 1);
		int score;
		try {
			score = std::stoi(scoreStr);
		}
		catch (...) {
			std::cerr << "Error converting score to integer: " << scoreStr << std::endl;
			continue; // Skip this line
		}

		// Add the pair to the data vector
		data.push_back(std::make_pair(name, score));
	}

	file.close();

	std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; // Sort in descending order of score
		});

	Texture2D backgroundImage = LoadTexture("./img/menu.png");
	while (!WindowShouldClose()) {

		DrawText("Score Table:", 280, 20, 40, DARKGRAY);



		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexture(backgroundImage, 0, 0, WHITE);
		int centerX = GetScreenWidth() / 2 -50;
		int centerY = 150;

		DrawText("name:", centerX -150, centerY , 50, LIGHTGRAY);
		DrawText("score:", centerX+150, centerY, 50, LIGHTGRAY);
		int y = centerY+80;
		for (const auto& pair : data) {
			DrawText(pair.first.c_str(), centerX - 100, y, 20, WHITE);
			DrawText(to_string(pair.second).c_str(), centerX + 200, y, 20, WHITE);
			y += 40;
		}

		EndDrawing();

		if (IsKeyPressed(KEY_SPACE)) {
			drawMenu();
			break;

		}

	}

}

void Game::goodbye() {
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("good bye ", 20, 50, 20, DARKGRAY);
	EndDrawing();

	CloseWindow();

}

void Game::drawGameScreen(ListOfShapes* shapelist, Shape* currentShape, Shape* nextShape) {

	if (shapelist == nullptr)
	{
		shapelist = new ListOfShapes();
		currentShape = new Shape();
		nextShape = new Shape();
		shapelist->appendShape(new Shape(), 's');
		shapelist->appendShape(new Shape(), 's');

	}
	bool newShapeNeeded = false;
	int selectedShape = -1;
	Shape* selected = nullptr;

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("Score:", 20, 20, 20, RAYWHITE);
		DrawText(TextFormat("%d", score), 100, 20, 20, RAYWHITE);

		DrawText("Current Shape:", 20, 50, 20, RAYWHITE);
		drawShape(currentShape, 100, 120);
		DrawText("Next Shape:", 550, 50, 20, RAYWHITE);
		drawShape(nextShape, 600, 120);


		if (IsKeyPressed(KEY_A)) {
			{
				shapelist->appendShape(currentShape, 's');
				selectedShape = -1;
				newShapeNeeded = true;
			}
		}
		else if (IsKeyPressed(KEY_D)) {
			{
				shapelist->appendShape(currentShape, 'e');
				selectedShape = -1;
				newShapeNeeded = true;
			}
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			if (selectedShape == -1)
				selectedShape = 0;
			else
			{
				selectedShape++;
				if (selectedShape >= shapelist->getShapeCount())
					selectedShape = 0;
			}


		}
		else if (IsKeyPressed(KEY_LEFT)) {
			if (selectedShape == -1)
				selectedShape = shapelist->getShapeCount() - 1;
			else
			{
				selectedShape--;
				if (selectedShape < 0)
				{
					selectedShape = shapelist->getShapeCount() - 1;
				}
			}


		}
		else if (IsKeyPressed(KEY_UP) && selected != nullptr) {
			shapelist->shiftShapesWithSameColor(selected->node->getColor());
		}
		else if (IsKeyPressed(KEY_DOWN) && selected != nullptr) {
			shapelist->shiftShapesWithSameName(selected->node->getName());
		}
		else if (IsKeyPressed(KEY_SPACE)) {
			selectedShape = -1;
			drawMenu();
			break;
		}
		else if (IsKeyPressed(KEY_S)) {
			storeGame(score);
			drawMenu();
		}


		DrawText("Shape List:", 20, 250, 20, RAYWHITE);
		const char* count = to_string(shapelist->getShapeCount()).c_str();
		DrawText("Count:", 450, 250, 20, RAYWHITE);


		DrawText(count, 600, 250, 20, RAYWHITE);

		DrawRoundedRectangle(0, 300, 1000, 120, 30, GRAY);
		DrawRoundedRectangle(10, 310, 980, 100, 30, WHITE);

		//y = 305; x = 10
		int x = 40;
		Shape* current = shapelist->getStart();
		selected = shapelist->getShape(selectedShape);
		if (selected != nullptr) {
			DrawText("press up to change with same color", 50, 450, 20, RED);
			DrawText("press down to change with same name", 50, 500, 20, RED);
		}
		while (current != nullptr) {
			if (selected != nullptr && selected == current) {
				drawShape(current, x, 300);
			}
			else
				drawShape(current, x, 360);

			x += 65;
			current = current->next;
		}

		shapelist->checkShapes(&score);

		if (newShapeNeeded) {
			currentShape = nextShape;
			nextShape = new Shape();
			newShapeNeeded = false;
		}

		EndDrawing();

		if (shapelist->getShapeCount() == 15)
		{
			break;
		}

	}
	goodbye();
}

void Game::storeGame(int score) {


	char name[10 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };
	bool mouseOnText = false;


	// Main game loop
	while (!WindowShouldClose()) {
		// Update
		if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
		else mouseOnText = false;

		if (mouseOnText) {
			// Set the window's cursor to the I-Beam
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			// Get char pressed (unicode character) on the queue
			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0) {
				// NOTE: Only allow keys in range [32..125]
				if ((key >= 32) && (key <= 125) && (letterCount < 9)) {
					name[letterCount] = (char)key;
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
		}
		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 9), 315, 250, 20, DARKGRAY);


		EndDrawing();

		if (IsKeyPressed(KEY_ENTER)) {
			break;
		}

	}

	// After closing the window, you can store the name in a file or use it as needed.
	std::string playerName = name; // Convert char array to string
	// Store the name in a file, use it in your game, etc.
	std::cout << "Player name: " << playerName << std::endl;

	std::string fileName = "game_data.txt";
	std::ofstream file(fileName, std::ios::app); // Open file in append mode

	file << playerName << " : " << score << std::endl;

	file.close();
	drawMenu();
}



int main() {
	srand(static_cast<unsigned int>(time(0)));

	Game game;
	game.drawMenu();




	return 0;
}
