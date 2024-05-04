#include "raylib.h"

int main()
{
	Image img = LoadImage("img/img.jpg");
	ExportImageAsCode(img, "blue.h");
	UnloadImage(img);

	img = LoadImage("img/menu_background.png");
	ExportImageAsCode(img, "bg.h");
	UnloadImage(img);
}