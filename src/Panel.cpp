#include "Panel.h"
#include "Window.h"

#include <iostream>

Panel::Panel() {
}

Panel::Panel(Window* windowParent) : windowParent(windowParent) {
	windowParent->getWindowPanel()->addPanel(this);
}

Panel::Panel(Panel* panelParent) : panelParent(panelParent) {
	panelParent->addPanel(this);
}

void Panel::addPanel(Panel* panel) {
	list.push_back(panel);
	panel->windowParent = windowParent;
	panel->panelParent = this;

	updatePanelQuad(this, panel);
	windowParent->addPanelQuad(&panel->pQuad);
}

const PanelType Panel::getPanelType() {
	return type;
}

const bool Panel::isVisible() { 
	return pQuad.visible; 
}

void Panel::setVisible(const bool visible) {
	pQuad.visible = visible;

	updatePanel();
}

const std::array<GLfloat, 2> Panel::getSize() {
	return std::array<GLfloat, 2> { getWidth(), getHeight() };
}

void Panel::setSize(const GLfloat Width, const GLfloat Height, const SizeType sizeType) {
	this->Width = Width;
	this->Height = Height;
	widthType = sizeType;
	heightType = sizeType;

	updatePanelChildren(this);
}

const GLfloat Panel::getWidth() {
	if(widthType == SIZE_PIXEL) {
		return (Width >= getMinWidth()) ? Width : getMinWidth();
	} else if(widthType == SIZE_PERCENT) {
		return (((panelParent->getWidth() / 100) * Width) >= getMinWidth()) ? ((panelParent->getWidth() / 100) * Width) : getMinWidth();
	}
}

const GLfloat Panel::getWidth(ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return pQuad.lines[3] - pQuad.lines[2];
	else if(valueType == VALUE_SETTED) {
		if(widthType == SIZE_PIXEL) {
			return (Width >= getMinWidth()) ? Width : getMinWidth();
		} else if(widthType == SIZE_PERCENT) {
			return (((panelParent->getWidth() / 100) * Width) >= getMinWidth()) ? ((panelParent->getWidth() / 100) * Width) : getMinWidth();
		}
	}
}

const GLfloat Panel::getMinWidth() {
	return (minWidthType == SIZE_PIXEL) ? minWidth : (panelParent->getWidth() / 100) * minWidth;
}

void Panel::setWidth(const GLfloat Width, const SizeType sizeType) {
	this->Width = Width;
	widthType = sizeType;

	updatePanelChildren(this);
}

void Panel::setMinWidth(const GLfloat minWidth, const SizeType sizeType) {
	this->minWidth = minWidth;
	minWidthType = sizeType;

	updatePanelChildren(this);
}

const GLfloat Panel::getHeight() {
	if(heightType == SIZE_PIXEL) {
		return (Height >= getMinHeight()) ? Height : getMinHeight();
	} else if(this->heightType == SIZE_PERCENT) {
		return (((panelParent->getHeight() / 100) * Height) >= getMinHeight()) ? ((panelParent->getHeight() / 100) * Height) : getMinHeight();
	}
}

const GLfloat Panel::getHeight(ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return pQuad.lines[1] - pQuad.lines[0];
	else if(valueType == VALUE_SETTED) {
		if(heightType == SIZE_PIXEL) {
			return (Height >= getMinHeight()) ? Height : getMinHeight();
		} else if(heightType == SIZE_PERCENT) {
			return (((panelParent->getHeight() / 100) * Height) >= getMinHeight()) ? ((panelParent->getHeight() / 100) * Height) : getMinHeight();
		}
	}
}

const GLfloat Panel::getMinHeight() {
	return (minHeightType == SIZE_PIXEL) ? minHeight : (panelParent->getHeight() / 100) * minHeight;
}

void Panel::setHeight(const GLfloat Height, const SizeType sizeType) {
	this->Height = Height;
	heightType = sizeType;

	updatePanelChildren(this);
}

void Panel::setMinHeight(const GLfloat minHeight, const SizeType sizeType) {
	this->minHeight = minHeight;
	minHeightType = sizeType;

	updatePanelChildren(this);
}

const std::array<GLfloat, 2> Panel::getPosition() {
	return std::array<GLfloat, 2> { getPosX(), getPosY() };
}

void Panel::setPosition(const GLfloat x, const GLfloat y, const SizeType sizeType) {
	this->x = x;
	this->y = y;
	posXType = sizeType;
	posYType = sizeType;

	updatePanelChildren(this);
}

const GLfloat Panel::getPosX() {
	return pQuad.lines[2] - panelParent->pQuad.lines[2];
}

const GLfloat Panel::getPosX(SizeType sizeType) {
	return (sizeType == SIZE_PIXEL) ? (pQuad.lines[2] - panelParent->pQuad.lines[2]) : ((pQuad.lines[2] - panelParent->pQuad.lines[2]) / panelParent->getWidth()) * 100;
}

const GLfloat Panel::getPosX(SizeType sizeType, ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return (sizeType == SIZE_PIXEL) ? (pQuad.lines[2] - panelParent->pQuad.lines[2]) : ((pQuad.lines[2] - panelParent->pQuad.lines[2]) / panelParent->getWidth()) * 100;
	else if(valueType == VALUE_SETTED) {
		if(sizeType == SIZE_PIXEL)
			return (posXType == SIZE_PIXEL) ? x : (panelParent->getWidth() / 100) * x;
		else if(sizeType == SIZE_PERCENT)
			return (posXType == SIZE_PERCENT) ? x : (x / panelParent->getWidth()) * 100;
	}
}

void Panel::setPosX(const GLfloat x, const SizeType sizeType) {
	this->x = x;
	posXType = sizeType;

	updatePanelChildren(this);
}

const GLfloat Panel::getPosY() {
	return pQuad.lines[0] - panelParent->pQuad.lines[0];
}

const GLfloat Panel::getPosY(SizeType sizeType) {
	return (sizeType == SIZE_PIXEL) ? (pQuad.lines[0] - panelParent->pQuad.lines[0]) : ((pQuad.lines[0] - panelParent->pQuad.lines[0]) / panelParent->getHeight()) * 100;
}

const GLfloat Panel::getPosY(SizeType sizeType, ValueType valueType) {
	if(valueType == VALUE_CALCULATED)
		return (sizeType == SIZE_PIXEL) ? (pQuad.lines[0] - panelParent->pQuad.lines[0]) : ((pQuad.lines[0] - panelParent->pQuad.lines[0]) / panelParent->getHeight()) * 100;
	else if(valueType == VALUE_SETTED) {
		if(sizeType == SIZE_PIXEL)
			return (posYType == SIZE_PIXEL) ? y : (panelParent->getHeight() / 100) * y;
		else if(sizeType == SIZE_PERCENT)
			return (posYType == SIZE_PERCENT) ? y : (y / panelParent->getHeight()) * 100;
	}
}

void Panel::setPosY(const GLfloat y, const SizeType sizeType) {
	this->y = y;
	posYType = sizeType;

	updatePanelChildren(this);
}

const std::array<Align, 4> Panel::getAlignments() {
	return pQuad.alignments;
}

const bool Panel::hasAlign(const Alignment alignment) {
	return (alignment != ALIGN_NONE) ? pQuad.alignments[alignment].alignType != ALIGN_NONE : false;
}

const GLfloat Panel::getAlign(const Alignment alignment) {
	if(alignment != ALIGN_NONE) {
		Align& align = pQuad.alignments[alignment];

		if(align.alignType == ALIGN_TOP || align.alignType == ALIGN_BOTTOM)
			return (align.sizeType == SIZE_PIXEL) ? align.offset : (panelParent->getHeight() / 100) * align.offset;
		else if (align.alignType == ALIGN_LEFT || align.alignType == ALIGN_RIGHT)
			return (align.sizeType == SIZE_PIXEL) ? align.offset : (panelParent->getWidth() / 100) * align.offset;
	}
}

void Panel::setAlign(const Alignment alignment, const GLfloat offset, const SizeType sizeType) {
	if(alignment != ALIGN_NONE) {
		pQuad.alignments[alignment] = { offset, sizeType, alignment };

		updatePanelChildren(this);
	}
}

const std::array<GLfloat, 4> Panel::getColor() {
	return pQuad.color;
}

const std::string Panel::getHexColor() {
	std::string hexColor = "#";

	for(int c = 0, index = 0; c < 6; c++, index = c / 2) {
		int val = (!(c % 2)) ? (pQuad.color[index] * 255) / 16 : (int)(pQuad.color[index] * 255) % 16;
		hexColor += (val < 10) ? val + '0' : (val - 10) + 'a';
	}

	return hexColor;
}

void Panel::setColor(const std::array<GLfloat, 4> color) {
	pQuad.color = color;

	updatePanel();
}

void Panel::setColor(const GLfloat color[4]) {
	pQuad.color = { color[0], color[1], color[2], color[3] };

	updatePanel();
}

void Panel::setHexColor(const std::string hexColor) {
	GLfloat colorBase[3] = { 0.0, 0.0, 0.0 };
	int c = 0, offset = 0, index = 0;
	
	for(; c < hexColor.size() && index <= 2; c++, index = (c - offset) / 2) {
		if(hexColor[c] == '#') {
			offset++; 
			continue;
		}

		int val = isdigit(hexColor[c]) ? hexColor[c] - '0' : (tolower(hexColor[c]) >= 'a' && tolower(hexColor[c]) <= 'f') ? tolower(hexColor[c]) - 'a' + 10 : 0;
		colorBase[index] = !((c - offset) % 2) ? val * 16 : colorBase[index] + val;
	}

	pQuad.color = { colorBase[0] / 255.0f, colorBase[1] / 255.0f, colorBase[2] / 255.0f, 1.0 };

	updatePanel();
}

void Panel::updatePanel() {
	if(pQuad.n_quad != -1) {
		updatePanelQuad(panelParent, this);
		windowParent->updateVertices(pQuad.n_quad);
	}
}

void Panel::updatePanelChildren(Panel* pParent) {
	pParent->updatePanel();

	for(int i = 0; i < pParent->list.size(); i++)
		updatePanelChildren(pParent->list[i]);
}

void Panel::updatePanelQuad(Panel* pParent, Panel* panel) {
	/* Calculation of the Lines to follow to display the GL_QUAD
	 *	line[0] = TOP LINE		(ALIGN_TOP =	0)
	 *	line[1] = BOTTOM LINE	(ALIGN_BOTTOM = 1)
	 *	line[2] = LEFT LINE		(ALIGN_LEFT =	2)
	 *	line[3] = RIGHT LINE	(ALIGN_RIGHT =	3)
	 */

	 //Top Line
	if(panel->hasAlign(ALIGN_TOP))
		panel->pQuad.lines[0] = pParent->pQuad.lines[0] + panel->getAlign(ALIGN_TOP);
	else if(panel->hasAlign(ALIGN_BOTTOM))
		panel->pQuad.lines[0] = ((pParent->pQuad.lines[0] + pParent->getHeight()) - panel->getAlign(ALIGN_BOTTOM)) - panel->getHeight(VALUE_SETTED);
	else
		panel->pQuad.lines[0] = pParent->pQuad.lines[0] + panel->getPosY(SIZE_PIXEL, VALUE_SETTED);

	//Bottom Line
	if(panel->hasAlign(ALIGN_BOTTOM))
		panel->pQuad.lines[1] = (pParent->pQuad.lines[0] + pParent->getHeight()) - panel->getAlign(ALIGN_BOTTOM);
	else
		panel->pQuad.lines[1] = panel->pQuad.lines[0] + panel->getHeight();

	//Left Line
	if(panel->hasAlign(ALIGN_LEFT))
		panel->pQuad.lines[2] = pParent->pQuad.lines[2] + panel->getAlign(ALIGN_LEFT);
	else if(panel->hasAlign(ALIGN_RIGHT))
		panel->pQuad.lines[2] = ((pParent->pQuad.lines[2] + pParent->getWidth()) - panel->getAlign(ALIGN_RIGHT)) - panel->getWidth();
	else
		panel->pQuad.lines[2] = pParent->pQuad.lines[2] + panel->getPosX(SIZE_PIXEL, VALUE_SETTED);

	//Right Line
	if(panel->hasAlign(ALIGN_RIGHT))
		panel->pQuad.lines[3] = (pParent->pQuad.lines[2] + pParent->getWidth()) - panel->getAlign(ALIGN_RIGHT);
	else
		panel->pQuad.lines[3] = panel->pQuad.lines[2] + panel->getWidth();

	if(panel->pQuad.lines[0] < pParent->pQuad.lines[0]) panel->pQuad.lines[0] = pParent->pQuad.lines[0];
	if(panel->pQuad.lines[1] > pParent->pQuad.lines[1]) panel->pQuad.lines[1] = pParent->pQuad.lines[1];
	if(panel->pQuad.lines[2] < pParent->pQuad.lines[2]) panel->pQuad.lines[2] = pParent->pQuad.lines[2];
	if(panel->pQuad.lines[3] > pParent->pQuad.lines[3]) panel->pQuad.lines[3] = pParent->pQuad.lines[3];

	//Visibility Conditions
	if((!pParent->isVisible())
	|| (panel->pQuad.lines[1] < panel->pQuad.lines[0])
	|| (panel->pQuad.lines[3] < panel->pQuad.lines[2])) {
		panel->pQuad.visible = false;
	} else {
		panel->pQuad.visible = true;
	}

}