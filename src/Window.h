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
		void setVisible(const bool visible);
		void addPanel(Panel* panel);

		GLFWwindow* getWindow();
		Panel* getWindowPanel();
		Panel* getPanelClicked(Panel* panel, const double posX, const double posY);

		const GLdouble getWidth();
		const GLdouble getHeight();

		const bool isVisible();

		std::map<std::array<int, 3>, void(*)()> slots;

		const int MAX_PANELS = 64; //64 panels
		int n_quads = 0;

		std::vector<Panel*> panelsQuad;

		void addPanelQuad(Panel* panel);
		void updateVertices(int n_quad);

		void InitGL();
		void SetupShaders();
		void ResizeWindow(int offset_width, int offset_height);
		void Display();

		GLuint Buffers[1];
		GLuint VAOs[1];

	private:
		Gui* gui;
		Panel windowPanel;
		GLFWwindow* window = nullptr;
		GLuint shaderProgram;

		GLdouble Width, Height;
		char* name = nullptr;
		bool visible = true;
};

#endif