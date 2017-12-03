#ifndef WINDOW_H
#define WINDOW_H

#include "Gui.h"
#include "Panel.h"

#include <functional>
#include <future>
#include <utility>
#include <map>

class Gui;

class Window {
	public:
		Window(Gui* gui, const double Width, const double Height, const char* name);
		~Window();

		GLFWwindow* getWindow();
		void setSize(const double Width, const double Height);

		void addPanel(Panel* panel);
		Panel* getPanelClicked(Panel* panel, const double posX, const double posY);

		Gui* gui;
		GLFWwindow* window = nullptr;
		Panel windowPanel;

		GLdouble Width, Height;
		char* name = nullptr;

		std::map<std::array<int, 4>, void(*)()> slots;
};

#endif