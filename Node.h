#pragma once
#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    string color;
    string name;

public :
    void setColor(const string& newColor);
    void setName(const string& newName);

    string getColor();
    string getName();

};

