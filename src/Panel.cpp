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

void Panel::addPanel(Panel* panel) {
	this->list.push_back(panel);
	panel->windowParent = this->windowParent;
	panel->panelParent = this;

	updatePanelQuad(this, panel);
	this->windowParent->addPanelQuad(&panel->pQuad);
}

const PanelType Panel::getPanelType() {
	return type;
}

const bool Panel::isVisible() { 
	return this->pQuad.visible; 
}

void Panel::setVisible(const bool visible) {
	this->pQuad.visible = visible;

	updatePanel();
}

const std::array<GLfloat, 2> Panel::getSize() {
	return std::array<GLfloat, 2> { this->getWidth(), this->getHeight() };
}

void Panel::setSize(const GLfloat Width, const GLfloat Height, const SizeType sizeType) {
	this->Width = Width;
	this->Height = Height;
	this->widthType = sizeType;
	this->heightType = sizeType;

	updatePanelChild(this);
}

const GLfloat Panel::getWidth() {
	if(this->widthType == SIZE_PIXEL) {
		return (this->Width >= this->getMinWidth()) ? this->Width : this->getMinWidth();
	} else if(this->widthType == SIZE_PERCENT) {
		return (((panelParent->getWidth() / 100) * this->Width) >= this->getMinWidth()) ? ((panelParent->getWidth() / 100) * this->Width) : this->getMinWidth();
	}
}

const GLfloat Panel::getMinWidth() {
	return (this->minWidthType == SIZE_PIXEL) ? this->minWidth : (panelParent->getWidth() / 100) * this->minWidth;
}

void Panel::setWidth(const GLfloat Width, const SizeType sizeType) {
	this->Width = Width;
	this->widthType = sizeType;

	updatePanelChild(this);
}

void Panel::setMinWidth(const GLfloat minWidth, const SizeType sizeType) {
	this->minWidth = minWidth;
	this->minWidthType = sizeType;

	updatePanelChild(this);
}

const GLfloat Panel::getHeight() {
	if(this->heightType == SIZE_PIXEL) {
		return (this->Height >= this->getMinHeight()) ? this->Height : this->getMinHeight();
	} else if(this->heightType == SIZE_PERCENT) {
		return (((panelParent->getHeight() / 100) * this->Height) >= this->getMinHeight()) ? ((panelParent->getHeight() / 100) * this->Height) : this->getMinHeight();
	}
}

const GLfloat Panel::getMinHeight() {
	return (this->minHeightType == SIZE_PIXEL) ? this->minHeight : (panelParent->getHeight() / 100) * this->minHeight;
}

void Panel::setHeight(const GLfloat Height, const SizeType sizeType) {
	this->Height = Height;
	this->heightType = sizeType;

	updatePanelChild(this);
}

void Panel::setMinHeight(const GLfloat minHeight, const SizeType sizeType) {
	this->minHeight = minHeight;
	this->minHeightType = sizeType;

	updatePanelChild(this);
}

const std::array<GLfloat, 2> Panel::getPosition() {
	return std::array<GLfloat, 2> { this->getPosX(), this->getPosY() };
}

void Panel::setPosition(const GLfloat x, const GLfloat y, const SizeType sizeType) {
	this->x = x;
	this->y = y;
	this->posXType = sizeType;
	this->posYType = sizeType;

	updatePanelChild(this);
}

const GLfloat Panel::getPosX() {
	return this->pQuad.lines[2] - panelParent->pQuad.lines[2];
}

const GLfloat Panel::getPosX(SizeType sizeType) {
	return (sizeType == SIZE_PIXEL) ? (this->pQuad.lines[2] - panelParent->pQuad.lines[2]) : ((this->pQuad.lines[2] - panelParent->pQuad.lines[2]) / panelParent->getWidth()) * 100;
}

const GLfloat Panel::getPosX(SizeType sizeType, ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return (sizeType == SIZE_PIXEL) ? (this->pQuad.lines[2] - panelParent->pQuad.lines[2]) : ((this->pQuad.lines[2] - panelParent->pQuad.lines[2]) / panelParent->getWidth()) * 100;
	else if(valueType == VALUE_SETTED) {
		if(sizeType == SIZE_PIXEL)
			return (this->posXType == SIZE_PIXEL) ? this->x : (panelParent->getWidth() / 100) * this->x;
		else if(sizeType == SIZE_PERCENT)
			return (this->posXType == SIZE_PERCENT) ? this->x : (this->x / panelParent->getWidth()) * 100;
	}
}

void Panel::setPosX(const GLfloat x, const SizeType sizeType) {
	this->x = x;
	this->posXType = sizeType;

	updatePanelChild(this);
}

const GLfloat Panel::getPosY() {
	return this->pQuad.lines[0] - panelParent->pQuad.lines[0];
}

const GLfloat Panel::getPosY(SizeType sizeType) {
	return (sizeType == SIZE_PIXEL) ? (this->pQuad.lines[0] - panelParent->pQuad.lines[0]) : ((this->pQuad.lines[0] - panelParent->pQuad.lines[0]) / panelParent->getHeight()) * 100;
}

const GLfloat Panel::getPosY(SizeType sizeType, ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return (sizeType == SIZE_PIXEL) ? (this->pQuad.lines[0] - panelParent->pQuad.lines[0]) : ((this->pQuad.lines[0] - panelParent->pQuad.lines[0]) / panelParent->getHeight()) * 100;
	else if(valueType == VALUE_SETTED) {
		if(sizeType == SIZE_PIXEL)
			return (this->posYType == SIZE_PIXEL) ? this->y : (panelParent->getHeight() / 100) * this->y;
		else if(sizeType == SIZE_PERCENT)
			return (this->posYType == SIZE_PERCENT) ? this->y : (this->y / panelParent->getHeight()) * 100;
	}
}

void Panel::setPosY(const GLfloat y, const SizeType sizeType) {
	this->y = y;
	this->posYType = sizeType;

	updatePanelChild(this);
}

const std::array<GLfloat, 4> Panel::getAlignments() {
	return pQuad.alignments;
}

void Panel::addAlignment(Alignment alignment, const GLfloat offset) {
	pQuad.alignments[alignment] = offset;
}

void Panel::setColor(GLfloat color[4]) {
	for (int i = 0; i < 4; i++)
		this->pQuad.quadColor[i] = color[i];

	updatePanel();
}

void Panel::updatePanel() {
	if (this->pQuad.n_quad != -1) {
		updatePanelQuad(this->panelParent, this);
		this->windowParent->updateVertices(this->pQuad.n_quad);
	}
}

void Panel::updatePanelChild(Panel* pChild) {
	pChild->updatePanel();

	for (int i = 0; i < pChild->list.size(); i++)
		updatePanelChild(pChild->list[i]);
}

void Panel::updatePanelQuad(Panel* pParent, Panel* panel) {
	/* Calculation of the Lines to follow to display the GL_QUAD
	 *	line[0] = TOP LINE		(ALIGN_TOP =	0)
	 *	line[1] = BOTTOM LINE	(ALIGN_BOTTOM = 1)
	 *	line[2] = LEFT LINE		(ALIGN_LEFT =	2)
	 *	line[3] = RIGHT LINE	(ALIGN_RIGHT =	3)
	 */

	 //Top Line
	if (panel->pQuad.alignments[ALIGN_TOP] != -1)
		panel->pQuad.lines[0] = pParent->pQuad.lines[0] + panel->pQuad.alignments[ALIGN_TOP];
	else if (panel->pQuad.alignments[ALIGN_BOTTOM] != -1)
		panel->pQuad.lines[0] = (pParent->pQuad.lines[1] - panel->pQuad.alignments[ALIGN_BOTTOM]) - panel->getHeight();
	else
		panel->pQuad.lines[0] = pParent->pQuad.lines[0] + panel->getPosY(SIZE_PIXEL, VALUE_SETTED);

	//Bottom Line
	if (panel->pQuad.alignments[ALIGN_BOTTOM] != -1)
		panel->pQuad.lines[1] = pParent->pQuad.lines[1] - panel->pQuad.alignments[ALIGN_BOTTOM];
	else
		panel->pQuad.lines[1] = panel->pQuad.lines[0] + panel->getHeight();

	//Left Line
	if (panel->pQuad.alignments[ALIGN_LEFT] != -1)
		panel->pQuad.lines[2] = pParent->pQuad.lines[2] + panel->pQuad.alignments[ALIGN_LEFT];
	else if (panel->pQuad.alignments[ALIGN_RIGHT] != -1)
		panel->pQuad.lines[2] = (pParent->pQuad.lines[3] - panel->pQuad.alignments[ALIGN_RIGHT]) - panel->getWidth();
	else
		panel->pQuad.lines[2] = pParent->pQuad.lines[2] + panel->getPosX(SIZE_PIXEL, VALUE_SETTED);

	//Right Line
	if (panel->pQuad.alignments[ALIGN_RIGHT] != -1)
		panel->pQuad.lines[3] = pParent->pQuad.lines[3] - panel->pQuad.alignments[ALIGN_RIGHT];
	else
		panel->pQuad.lines[3] = panel->pQuad.lines[2] + panel->getWidth();

	//Visibility Conditions
	if (!pParent->pQuad.visible) panel->pQuad.visible = false;
}