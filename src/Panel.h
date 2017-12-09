#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

struct Align {
	Alignment alignment;
	GLdouble offset;

	Align(Alignment alignment, GLdouble offset)
		: alignment(alignment), offset(offset) {
	}
};

class Panel{
	public:
		Panel();
		Panel(Window* windowParent);
		void setSize(const GLdouble Width, const GLdouble Height);
		void setPosition(const GLdouble x, const GLdouble y);
		void setVisible(const bool visible);
		void addPanel(Panel* panel);
		void addAlignment(Align align);

		const GLdouble getWidth();
		const GLdouble getHeight();
		
		const GLdouble getPosX();
		const GLdouble getPosY();

		const std::vector<Align> getAlignments();

		const bool isVisible();

		std::map<std::array<int, 3>, void(*)()> slots;
		std::vector<Panel*> list{};
		Window* windowParent = nullptr;

	private:
		GLdouble Width = 0, Height = 0;
		GLdouble x = 0, y = 0;
		bool visible = true;
		std::vector<Align> alignments;
};

#endif