//#include "Game.h"
//
//Game::Game() {
//	screenWidth =600;
//	screenHeight = 600;
//	fps =60;
//
//	InitWindow(screenWidth, screenHeight, "Tetris game");
//
//	SetTargetFPS(fps);
//};
//
//void Game::menu() {
//	Texture2D background = LoadTexture("img/1.png");
//
//	const char* menuOptions[] = {
//		"Start New Game",
//		"Load Saved Game",
//		"Game Controls",
//		"Game Rules",
//		"levels",
//		"Recorded Scores",
//		"Exit" };
//
//	int selectedOption = 0;
//
//	while (!WindowShouldClose())
//	{
//		ClearBackground(RAYWHITE);
//
//		DrawTexture(background, 0, 0, WHITE);
//
//		for (int i = 0; i < 7; i++)
//		{
//			if (i == selectedOption)
//			{
//				DrawText(">", screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2 - 20, 156 + i * 40 - 4, 30, BLUE);
//				DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 156 + i * 40, 20, RED);
//			}
//			else
//			{
//				DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 156 + i * 40, 20, BLACK);
//			}
//		}
//
//		if (IsKeyPressed(KEY_UP))
//		{
//			selectedOption--;
//			if (selectedOption < 0)
//				selectedOption = 6;
//		}
//		else if (IsKeyPressed(KEY_DOWN))
//		{
//			selectedOption++;
//			if (selectedOption > 6)
//				selectedOption = 0;
//		}
//		else if (IsKeyPressed(KEY_ENTER))
//		{
//			UnloadTexture(background);
//			UnloadTexture(background);
//			EndDrawing();
//			return static_cast<MenuOption>(selectedOption);
//		}
//		EndDrawing();
//	}
//	UnloadTexture(background);
//	return EXIT;
//}