#include "TModel.h"

TModel::TModel(std::vector<std::string> symbols, int width, int height) {
	screenBuffer = symbols;

	this->width = width;
	this->height = height;
	//length = strlen(symbols);
}

void TModel::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

Position TModel::getPosition() {
	return { x, y };
}

Size TModel::getSize() {
	return { width, height };
}

void TModel::move(float x, float y) {
	this->x += x;
	this->y += y;
}

unsigned TModel::getLength() const {
	return length;
}