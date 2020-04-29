#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

struct Align {
	GLfloat		offset;
	SizeType	sizeType;
	Alignment	alignType = ALIGN_NONE;
};

struct PanelQuad {
	bool visible = true;	//by default the panel is visible
	int n_quad = -1;		//by default the panel is not binded with a window
	std::array<GLfloat, 4> color = { 0.941176, 0.941176, 0.941176, 1.0 };	//default panel color
	std::array<Align, 4> alignments;										
	std::array<GLfloat, 4> lines = { 0.0, 0.0, 0.0, 0.0 };					//default panel lines to make the Quad
};

class Panel {
	public:
		Panel();
		Panel(Window* windowParent);
		Panel(Panel* panelParent);

		void addPanel(Panel* panel);
		const PanelType getPanelType();
		void updatePanel();

		/* Visible */
		const bool isVisible();
		void setVisible(const bool visible);

		/* Size (Width + Height) */
		const std::array<GLfloat, 2> getSize();
		void setSize(const GLfloat Width, const GLfloat Height, const SizeType sizeType);

		/* Width */
		const GLfloat getWidth();
		const GLfloat getWidth(ValueType valueType);
		const GLfloat getMinWidth();
		void setWidth(const GLfloat Width, const SizeType sizeType);
		void setMinWidth(const GLfloat minWidth, const SizeType sizeType);

		/* Height */
		const GLfloat getHeight();
		const GLfloat getHeight(ValueType valueType);
		const GLfloat getMinHeight();
		void setHeight(const GLfloat Height, const SizeType sizeType);
		void setMinHeight(const GLfloat minHeight, const SizeType sizeType);
		
		/* Position (X + Y) */
		const std::array<GLfloat, 2> getPosition();
		void setPosition(const GLfloat x, const GLfloat y, const SizeType sizeType);

		/* X */
		const GLfloat getPosX();
		const GLfloat getPosX(SizeType sizeType);
		const GLfloat getPosX(SizeType sizeType, ValueType valueType);
		void setPosX(const GLfloat x, const SizeType sizeType);

		/* Y */
		const GLfloat getPosY();
		const GLfloat getPosY(SizeType sizeType);
		const GLfloat getPosY(SizeType sizeType, ValueType valueType);
		void setPosY(const GLfloat y, const SizeType sizeType);

		/* Alignments (ALIGN_TOP, ALIGN_BOTTOM, ALIGN_LEFT, ALIGN_RIGHT) */
		const std::array<Align, 4> getAlignments();
		const bool hasAlign(const Alignment alignment);
		const GLfloat getAlign(const Alignment alignment);
		void setAlign(const Alignment alignment, const GLfloat offset, const SizeType sizeType);

		/* Color */
		const std::array<GLfloat, 4> getColor();
		void setColor(const GLfloat color[4]);
		void setColor(const std::array<GLfloat, 4> color);
		void Panel::setColor(const std::string htmlColor);

		std::map<std::array<int, 3>, void(*)()> slots;
		std::vector<Panel*> list{};
		Window* windowParent = nullptr;
		Panel* panelParent = nullptr;
		PanelQuad pQuad;

		virtual void addChar(const char c) {};
		virtual void removeChar() {};

	private:
		void updatePanelChildren(Panel* pParent);
		void updatePanelQuad(Panel* pParent, Panel* panel);

	protected:
		PanelType type = PANEL;

		GLfloat x = 0, y = 0;
		SizeType posXType = SIZE_PIXEL, posYType = SIZE_PIXEL;
		
		GLfloat Width = 0, Height = 0;
		SizeType widthType = SIZE_PIXEL, heightType = SIZE_PIXEL;

		GLfloat minWidth = 0, minHeight = 0;
		SizeType minWidthType = SIZE_PIXEL, minHeightType = SIZE_PIXEL;
};

#endif