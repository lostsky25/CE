#pragma once
#include <string>
#include <vector>

struct Position {
	float x;
	float y;
};

struct Size {
	int width;
	int height;
};

class TModel
{
public:
	TModel(std::vector<std::string>, int, int);
	void setPosition(int, int);
	Position getPosition();
	Size getSize();
	void move(float, float);
	unsigned getLength() const;

private:
	std::vector<std::string> screenBuffer;

	int width;
	int height;

	unsigned length;

	float x = 0;
	float y = 0;


	friend class CEngine;
};

