#include "Panel.h"

#include <iostream>

Panel::Panel() {
}

void Panel::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;
}

void Panel::setPosition(const double x, const double y) {
	this->x = x;
	this->y = y;
}

void Panel::addPanel(Panel* panel) {
	list.push_back(panel);
}