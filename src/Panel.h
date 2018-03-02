#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

struct PanelQuad {
	bool visible = true;
	int n_quad = -1;
	GLdouble quadSize[2] {0.0, 0.0};
	GLdouble quadPos[2] {0.0, 0.0};
	GLfloat quadColor[4] {0.0, 0.0, 0.0, 1.0};
	std::array<GLdouble, 4> alignments = {-1, -1, -1, -1};
};

class Panel {
	public:
		Panel();
		Panel(Window* windowParent);
		Panel(Panel* panelParent);
		void updatePanel();
		void updatePanelQuad(Panel* panelParent, Panel* panel);
		void updatePanelChild(Panel* pParent);
		void setSize(const GLdouble Width, const GLdouble Height);
		void setPosition(const GLdouble x, const GLdouble y);
		void setVisible(const bool visible);
		void setColor(GLfloat color[4]);
		void addPanel(Panel* panel);
		void addAlignment(Alignment alignment, const GLdouble offset);

		const GLdouble getWidth();
		const GLdouble getHeight();
		
		const GLdouble getPosX();
		const GLdouble getPosY();

		const std::array<GLdouble, 4> getAlignments();

		const PanelType getPanelType();

		const bool isVisible();

		std::map<std::array<int, 3>, void(*)()> slots;
		std::vector<Panel*> list{};
		Window* windowParent = nullptr;
		Panel* panelParent = nullptr;
		PanelQuad pQuad;

		virtual void addChar(const char c) {};
		virtual void removeChar() {};

	protected:
		PanelType type = PANEL;
		GLdouble x = 0, y = 0;
		GLdouble Width = 0, Height = 0;
};

#endif