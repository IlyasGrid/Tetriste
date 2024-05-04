#pragma once
#include "Shape.h"
#include <vector>

using namespace std;
class ListOfShapes
{
	Shape* start;
	Shape* end;
	int shapeCount;

	void appendShapeAtStart(Shape* shape);
	void appendShapeAtEnd(Shape* shape);

public:



	ListOfShapes() : start(nullptr), end(nullptr), shapeCount(0) {} // initialise all

	~ListOfShapes();


	// Setters
	void setStart(Shape* newStart);
	void setEnd(Shape* newEnd);
	void setShapeCount(int count);

	// Getters
	Shape* getStart();
	Shape* getEnd();
	int getShapeCount();

	bool isEmpty() const;

	void appendShape(Shape* shape, char where); 

	void checkShapes(int* score);

	void removeShape(Shape* shape);

	void shiftShapesWithSameColor(string color);

	void shiftShapesWithSameName(string name);

	Shape * getShape(int index);

	void establishShapeConnections();

	vector<Shape> getShapes();


};

