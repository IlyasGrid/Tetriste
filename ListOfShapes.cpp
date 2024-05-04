#include "ListOfShapes.h"

//	Destructeur
ListOfShapes :: ~ListOfShapes() {
	Shape* current = start;
	while (current != nullptr) {
		Shape* temp = current;
		current = current->next;
		delete temp;
	}
}

// Setters
void ListOfShapes::setStart(Shape* newStart) {
	start = newStart;
}

void ListOfShapes::setEnd(Shape* newEnd) {
	end = newEnd;
}

void ListOfShapes::setShapeCount(int count) {
	shapeCount = count;
}

// Getters

Shape* ListOfShapes::getStart() {
	return start;
}

Shape* ListOfShapes::getEnd() {
	return end;
}

int ListOfShapes::getShapeCount() {
	return shapeCount;
}


// List emptiness verification
bool ListOfShapes::isEmpty() const {
	if (this->start == nullptr)
	{
		return true;
	}
	else {
		return false;
	}
}

// Append at the start of the List
void ListOfShapes::appendShapeAtStart(Shape* shape) {

	shape->next = start;
	start->previous = shape;
	start = shape;
	shape->previous = nullptr;


}

// Append at the end of the List
void ListOfShapes::appendShapeAtEnd(Shape* shape) {

	end->next = shape;
	shape->previous = end;
	end = shape;
	shape->next = nullptr;

}

// Append a shape in the list S (for start) ,E (for End) 
void ListOfShapes::appendShape(Shape* shape, char where) {

	if (this->isEmpty()) {

		start = shape;
		end = shape;
		shape->next = nullptr;
		shape->previous = nullptr;
		

	}
	else
	if (where == 's' || where == 'S')
		appendShapeAtStart(shape);
	else if (where == 'e' || where == 'E')
		appendShapeAtEnd(shape);


	establishShapeConnections();
	shapeCount++;
}

// Check if there is three Shapes with one proprity commun
void ListOfShapes::checkShapes(int* score) {

	if (isEmpty() || shapeCount < 3) {
		return;
	}
	Shape* current = this->getStart();
	while (current != nullptr && current->next != nullptr && current->next->next != nullptr) {
		bool sameColor = (current->node->getColor() == current->next->node->getColor()) && (current->node->getColor() == current->next->next->node->getColor());
		bool sameName = (current->node->getName() == current->next->node->getName()) && (current->node->getName() == current->next->next->node->getName());

		if (sameColor && sameName) {
			(*score) += 1000;
			removeShape(current->next->next);
			removeShape(current->next);
			Shape* temp = current->next;
			removeShape(current);
			current = temp;
		}
		else if (sameColor || sameName) {
			(*score) += 300;
			removeShape(current->next->next);
			removeShape(current->next);
			Shape* temp = current->next;
			removeShape(current);
			current = temp;
		}
		else {
			current = current->next;
		}
	}
}

// Delete shape from the List 
void ListOfShapes::removeShape(Shape* shape) {
	// Verify if the list is Empty
	if (shape == nullptr || this->isEmpty()) {
		return;
	}
	// delete from the strat
	if (shape == start) {
		start = shape->next;
		if (start != nullptr) {
			start->previous = nullptr;
		}
		else {
			end = nullptr;
		}
	}

	// delet from the end
	else if (shape == end) {
		end = shape->previous;
		if (end != nullptr) {
			end->next = nullptr;
		}
		else {
			start = nullptr;
		}
	}
	// delete from the center
	else {
		Shape* prev = shape->previous;
		Shape* next = shape->next;
		prev->next = next;
		next->previous = prev;
	}

	// delete shape links
	shape->previous = nullptr;
	shape->next = nullptr;

	delete shape;
	shapeCount--;

	establishShapeConnections();
}

// Shift the  shapes with the same color
void ListOfShapes::shiftShapesWithSameColor(string color) {
	if (isEmpty()) {
		return;
	}

	Shape* current = start;
	Shape* firstShapeWithColor = nullptr;
	Shape* lastShapeWithColor = nullptr;

	// Find the first and last shape with the given color
	while (current != nullptr) {
		if (current->node->getColor() == color) {
			if (firstShapeWithColor == nullptr) {
				firstShapeWithColor = current;
			}
			lastShapeWithColor = current;
		}
		current = current->next;
	}

	// If no shape with the given color is found, return
	if (firstShapeWithColor == nullptr) {
		return;
	}

	// Shift the names of shapes with the given color
	current = firstShapeWithColor;
	string temp = current->node->getName();
	Shape* shapeWithTempName = nullptr;

	while (current != nullptr && current != lastShapeWithColor) {

		string helper = current->node->getName();
		current->node->setName(lastShapeWithColor->node->getName());
		lastShapeWithColor->node->setName(helper);

		current = current->nextColor;
	}


	establishShapeConnections();

}

// Shift the  shapes with the same name
void ListOfShapes::shiftShapesWithSameName(string name) {

	if (isEmpty()) {
		return;
	}

	Shape* current = start;
	Shape* firstShapeWithName = nullptr;
	Shape* lastShapeWithName = nullptr;

	// Find the first and last shape with the given color
	while (current != nullptr) {
		if (current->node->getName() == name) {
			if (firstShapeWithName == nullptr) {
				firstShapeWithName = current;
			}
			lastShapeWithName = current;
		}
		current = current->next;
	}

	// If no shape with the given color is found, return
	if (firstShapeWithName == nullptr) {
		return;
	}

	// Shift the names of shapes with the given color
	current = firstShapeWithName;
	string temp = current->node->getColor();
	Shape* shapeWithTempName = nullptr;

	while (current != nullptr && current != lastShapeWithName) {

		string helper = current->node->getColor();
		current->node->setColor(lastShapeWithName->node->getColor());
		lastShapeWithName->node->setColor(helper);

		current = current->nextShape;
	}
}

Shape* ListOfShapes::getShape(int index)
{
	Shape* current = start;
	int i = 0;
	while (current != nullptr) {
		if (i == index)
			return current;
		i++;
		current = current->next;
	}
		
	return nullptr;
}



// ReVerify the links between the shapes 
void ListOfShapes::establishShapeConnections() {
	if (isEmpty()) {
		return;
	}

	Shape* current = start;

	while (current != nullptr) {
		Shape* nextShapeSameColor = nullptr;
		Shape* nextShapeSameName = nullptr;

		Shape* helper = current->next;
		while (helper != nullptr) {
			if (nextShapeSameColor == nullptr && helper->node->getColor() == current->node->getColor()) {
				nextShapeSameColor = helper;
			}
			if (nextShapeSameName == nullptr && helper->node->getName() == current->node->getName()) {
				nextShapeSameName = helper;
			}
			if (nextShapeSameColor != nullptr && nextShapeSameName != nullptr) {
				break; // No need to continue searching if both connections are found
			}
			helper = helper->next;
		}

		current->nextColor = nextShapeSameColor;
		current->nextShape = nextShapeSameName;

		current = current->next;
	}
}


// transfer the list to vector
vector<Shape> ListOfShapes::getShapes()
{
	vector<Shape> shapes;
	Shape* current = start;
	while (current != nullptr) {
		shapes.push_back(*current);
		current = current->next;
	}

	return shapes;
}