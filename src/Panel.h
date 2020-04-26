#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

struct PanelQuad {
	bool visible = true;
	int n_quad = -1;
	GLfloat quadColor[4] {0.0, 0.0, 0.0, 1.0};
	std::array<GLfloat, 4> alignments = { -1, -1, -1, -1 };
	std::array<GLfloat, 4> lines = { 0.0, 0.0, 0.0, 0.0 };
};

class Panel {
	public:
		Panel();
		Panel(Window* windowParent);
		Panel(Panel* panelParent);

		void addPanel(Panel* panel);
		const PanelType getPanelType();

		/* Visible */
		const bool isVisible();
		void setVisible(const bool visible);

		/* Size (Width + Height) */
		const std::array<GLfloat, 2> getSize();
		void setSize(const GLfloat Width, const GLfloat Height, const SizeType sizeType);

		/* Width */
		const GLfloat getWidth();
		const GLfloat getMinWidth();
		void setWidth(const GLfloat Width, const SizeType sizeType);
		void setMinWidth(const GLfloat minWidth, const SizeType sizeType);

		/* Height */
		const GLfloat getHeight();
		const GLfloat getMinHeight();
		void setHeight(const GLfloat Height, const SizeType sizeType);
		void setMinHeight(const GLfloat minHeight, const SizeType sizeType);
		
		/* Position (X + Y) */
		const std::array<GLfloat, 2> getPosition();
		void setPosition(const GLfloat x, const GLfloat y, const SizeType sizeType);

		/* X */
		const GLfloat getPosX();
		void setPosX(const GLfloat x, const SizeType sizeType);

		/* Y */
		const GLfloat getPosY();
		void setPosY(const GLfloat y, const SizeType sizeType);

		/* Alignments (ALIGN_TOP, ALIGN_BOTTOM, ALIGN_LEFT, ALIGN_RIGHT) */
		const std::array<GLfloat, 4> getAlignments();
		void addAlignment(const Alignment alignment, const GLfloat offset);

		/* Color */
		void setColor(GLfloat color[4]);

		std::map<std::array<int, 3>, void(*)()> slots;
		std::vector<Panel*> list{};
		Window* windowParent = nullptr;
		Panel* panelParent = nullptr;
		PanelQuad pQuad;

		virtual void addChar(const char c) {};
		virtual void removeChar() {};
	private:
		void updatePanel();
		void updatePanelChild(Panel* pParent);
		void updatePanelQuad(Panel* panelParent, Panel* panel);

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