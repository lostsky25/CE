#pragma once
#include <string>
#include <Windows.h>

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
	TModel(CHAR_INFO*, int, int, int);
	void setPosition(int, int);
	Position getPosition();
	Size getSize();
	void move(float, float);
	unsigned getLength() const;

private:
	CHAR_INFO* screenBuffer;

	int width;
	int height;

	unsigned length;

	float x = 0;
	float y = 0;

	friend class CEngine;
};

