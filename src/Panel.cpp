#include "Panel.h"
#include "Window.h"

#include <iostream>

Panel::Panel() {
}

Panel::Panel(Window* windowParent) : windowParent(windowParent) {
	this->windowParent->getWindowPanel()->addPanel(this);
}

Panel::Panel(Panel* panelParent) : panelParent(panelParent) {
	this->panelParent->addPanel(this);
}

void Panel::updatePanel() {
	if(this->pQuad.n_quad != -1) {
		updatePanelQuad(this->panelParent, this);
		this->windowParent->updateVertices(this->pQuad.n_quad);
	}
}

void Panel::updatePanelQuad(Panel* pParent, Panel* panel) {
	if(!pParent->pQuad.visible) panel->pQuad.visible = false;

	if((panel->x + panel->Width) > pParent->Width) panel->pQuad.quadSize[0] = pParent->Width - panel->x;
	else panel->pQuad.quadSize[0] = panel->Width;

	if((panel->y + panel->Height) > pParent->Height) panel->pQuad.quadSize[1] = pParent->Height - panel->y;
	else panel->pQuad.quadSize[1] = panel->Height;

	if(panel->x > pParent->Width) panel->pQuad.quadSize[0] = 0;
	else panel->pQuad.quadPos[0] = pParent->pQuad.quadPos[0] + panel->x;

	if(panel->y > pParent->Height) panel->pQuad.quadSize[1] = 0;
	else panel->pQuad.quadPos[1] = pParent->pQuad.quadPos[1] + panel->y;
}

void Panel::updatePanelChild(Panel* pChild) {
	pChild->updatePanel();

	for(int i = 0; i < pChild->list.size(); i++)
		updatePanelChild(pChild->list[i]);
}

void Panel::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;

	updatePanelChild(this);
}

void Panel::setPosition(const double x, const double y) {
	this->x = x;
	this->y = y;

	updatePanelChild(this);
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
	panel->panelParent = this;

	updatePanelQuad(this, panel);

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