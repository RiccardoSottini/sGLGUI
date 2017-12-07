#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

class Panel{
	public:
		Panel();
		void setSize(const GLdouble Width, const GLdouble Height);
		void setPosition(const GLdouble x, const GLdouble y);
		void setVisible(const bool visible);
		void addPanel(Panel* panel);

		const GLdouble getWidth();
		const GLdouble getHeight();
		
		const GLdouble getPosX();
		const GLdouble getPosY();

		const bool isVisible();

		std::map<std::array<int, 3>, void(*)()> slots;
		std::vector<Panel*> list{};

	private:
		GLdouble Width = 0, Height = 0;
		GLdouble x = 0, y = 0;
		bool visible = true;
};

#endif