#include "Panel.h"
#include "Window.h"

#include <iostream>

Panel::Panel() {
	// color = {1.0, 1.0, 1.0, 1.0}  WHITE
	this->pQuad = {{0.0, 0.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}}; //size(width,height)  pos(x,y)  color(r,g,b,a)
}

Panel::Panel(Window* windowParent) : windowParent(windowParent) {
	this->windowParent->getWindowPanel()->addPanel(this);
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

void Panel::setColor(GLfloat color[4]) {
	for(int i = 0; i < 4; i++)
		this->pQuad.quadColor[i] = color[i];
}

void Panel::addPanel(Panel* panel) {
	list.push_back(panel);
	panel->windowParent = this->windowParent;

	if((panel->x + panel->Width) > this->Width) panel->pQuad.quadSize[0] = this->Width - panel->x;
	else panel->pQuad.quadSize[0] = panel->Width;

	if((panel->y + panel->Height) > this->Height) panel->pQuad.quadSize[1] = this->Height - panel->y;
	else panel->pQuad.quadSize[1] = panel->Height;

	panel->pQuad.quadPos[0] = panel->x;
	panel->pQuad.quadPos[1] = panel->y;

	this->windowParent->addPanelQuad(panel);
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