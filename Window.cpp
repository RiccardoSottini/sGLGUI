#include "Window.h"
#include "Event.h"

Window::Window(Gui* gui, const double Width, const double Height, const char* name) {
	this->gui = gui;
	this->window = glfwCreateWindow(Width, Height, name, NULL, NULL);
	setSize(Width, Height);
	this->name = (char*) name;

	gui->windows.push_back(this);
	gui->glfw_windows[this->window] = this;

	glfwMakeContextCurrent(this->window);
}

Window::~Window() {
}

GLFWwindow* Window::getWindow() {
	return this->window;
}

void Window::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;

	this->windowPanel.setSize(Width, Height);
}

void Window::addPanel(Panel* panel) {
	this->windowPanel.addPanel(panel);
}

Panel* Window::getPanelClicked(Panel* panel, const double posX, const double posY) {
	for(int i = panel->list.size() - 1; i >= 0; i--) {
		Panel* selected = panel->list[i];

		if((posX >= selected->x) && (posX <= selected->x + selected->Width) &&
	  	   (posY >= selected->y) && (posY <= selected->y + selected->Height)) {
			return getPanelClicked(selected, posX - selected->x, posY - selected->y);
		}
	}

	return panel;
}