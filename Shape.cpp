#include "Shape.h" 
#include <string>
#include <iostream>
using namespace std;

// Constructor
Shape::Shape() {

	int randomcolor = rand() % 4; // 0 to 3 for colors

	int randomshape = rand() % 4; // 0 to 3 for shapes

	node = new Node();

	switch (randomcolor)
	{
	case 0:
		node->setColor("red");
		break;
	case 1:
		node->setColor("yellow");
		break;
	case 2:
		node->setColor("blue");
		break;
	case 3:
		node->setColor("green");
		break;

	default:
		break;
	}

	switch (randomshape)
	{
	case 0:
		node->setName("TRIANGLE");
		break;
	case 1:
		node->setName("LOSANGE");
		break;
	case 2:
		node->setName("CIRCLE");
		break;
	case 3:
		node->setName("SQUARE");
		break;

	default:
		break;
	}


	next = nullptr;
	previous = nullptr;
	nextColor = nullptr;
	nextShape = nullptr;
}

Shape::Shape(string shapeName, string shapeColor) {
	node = new Node();
	node->setName(shapeName);
	node->setColor(shapeColor);
	next = nullptr;
	previous = nullptr;
	nextColor = nullptr;
	nextShape = nullptr;
}

// Destructor
Shape::~Shape() {
	delete node;
}