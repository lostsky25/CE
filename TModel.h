#pragma once
#include <string>

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
	TModel(const char*, int, int);
	void setPosition(int, int);
	Position getPosition();
	Size getSize();
	void move(float, float);
	unsigned getLength() const;

private:
	char* screenBuffer;

	int width;
	int height;

	unsigned length;

	float x = 0;
	float y = 0;

	friend class Engine;
};

