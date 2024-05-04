#pragma once
#include "Node.h"
class Shape
{
public:

	Node* node;

	Shape* next;
	Shape* previous;

	Shape* nextColor;
	Shape* nextShape;



	Shape();
	Shape(string shapeName, string shapeColor);

	~Shape();

};

