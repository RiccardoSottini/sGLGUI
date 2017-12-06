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
		void setSize(const double Width, const double Height);
		void addPanel(Panel* panel);

		GLFWwindow* getWindow();
		Panel* getWindowPanel();
		Panel* getPanelClicked(Panel* panel, const double posX, const double posY);

		const GLdouble getWidth();
		const GLdouble getHeight();

		std::map<std::array<int, 3>, void(*)()> slots;

	private:
		Gui* gui;
		Panel windowPanel;
		GLFWwindow* window = nullptr;

		GLdouble Width, Height;
		char* name = nullptr;
};

#endif