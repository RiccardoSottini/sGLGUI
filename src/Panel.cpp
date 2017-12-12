#include "Panel.h"
#include "Window.h"

#include <iostream>

Panel::Panel() {
}

Panel::Panel(Window* windowParent) : windowParent(windowParent) {
	this->windowParent->getWindowPanel()->addPanel(this);
}

void Panel::updatePanel() {
	if(this->pQuad.n_quad != -1)
		this->windowParent->updateVertices(this->pQuad.n_quad);
}

void Panel::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;

	this->pQuad.quadSize[0] = Width;
	this->pQuad.quadSize[1] = Height;

	updatePanel();
}

void Panel::setPosition(const double x, const double y) {
	this->x = x;
	this->y = y;

	this->pQuad.quadPos[0] = x;
	this->pQuad.quadPos[1] = y;

	updatePanel();
}

void Panel::setVisible(const bool visible) {
	this->pQuad.visible = visible;

	updatePanel();
}

void Panel::setColor(GLfloat color[4]) {
	for(int i = 0; i < 4; i++)
		this->pQuad.quadColor[i] = color[i];

	updatePanel();
}

void Panel::addPanel(Panel* panel) {
	list.push_back(panel);
	panel->windowParent = this->windowParent;

	if((panel->x + panel->Width) > this->Width) panel->pQuad.quadSize[0] = this->Width - panel->x;
	else panel->pQuad.quadSize[0] = panel->Width;

	if((panel->y + panel->Height) > this->Height) panel->pQuad.quadSize[1] = this->Height - panel->y;
	else panel->pQuad.quadSize[1] = panel->Height;

	if(panel->x > this->Width) panel->pQuad.quadSize[0] = 0;
	else panel->pQuad.quadPos[0] = this->x + panel->x;

	if(panel->y > this->Height) panel->pQuad.quadSize[1] = 0;
	else panel->pQuad.quadPos[1] = this->y + panel->y;

	this->windowParent->addPanelQuad(&panel->pQuad);
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
	return this->pQuad.visible;
}