#ifndef PANEL_H
#define PANEL_H

#include "Gui.h"

#include <string>

class Panel{
	public:
		Panel();
		void setSize(const GLdouble Width, const GLdouble Height);
		void setPosition(const GLdouble x, const GLdouble y);
		void addPanel(Panel* panel);

		GLdouble Width = 0, Height = 0;
		GLdouble x = 0, y = 0;
		std::vector<Panel*> list{};

		std::map<std::array<int, 4>, void(*)()> slots;
};

#endif