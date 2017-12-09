#include "Panel.h"

#include <iostream>

Panel::Panel() {
}

Panel::Panel(Window* windowParent) : windowParent(windowParent) {
}

void Panel::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;
}

void Panel::setPosition(const double x, const double y) {
	this->x = x;
	this->y = y;
}

void Panel::setVisible(const bool visible) {
	this->visible = visible;
}

void Panel::addPanel(Panel* panel) {
	list.push_back(panel);
	panel->windowParent = this->windowParent;
}

void Panel::addAlignment(Align align) {
	alignments.push_back(align);
}

const GLdouble Panel::getWidth() {
	return Width;
}

const GLdouble Panel::getHeight() {
	return Height;
}

const GLdouble Panel::getPosX() {
	return x;
}

const GLdouble Panel::getPosY() {
	return y;
}

const std::vector<Align> Panel::getAlignments() {
	return alignments;
}

const bool Panel::isVisible() {
	return visible;
}