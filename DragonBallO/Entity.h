#pragma once

#include <string>

class Entity
{
public:
	Entity();
	~Entity();
protected:
	std::string name;
	int mHealth;
	int mXPos;
	int mYPos;
};

