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
		Window(Gui* gui, const GLfloat Width, const GLfloat Height, const char* name);
		void setSize(const GLfloat Width, const GLfloat Height);
		void setVisible(const bool visible);
		void addPanel(Panel* panel);

		GLFWwindow* getWindow();
		Panel* getWindowPanel();
		Panel* getPanelClicked(Panel* panel, const GLfloat posX, const GLfloat posY);

		const GLfloat getWidth();
		const GLfloat getHeight();

		const bool isVisible();

		std::map<std::array<int, 3>, void(*)()> slots;

		const int MAX_PANELS = 64; //64 panels
		int n_quads = 0;

		std::vector<PanelQuad*> panelsQuad;

		void addPanelQuad(PanelQuad* pQuad);
		void updateVertices(int n_quad);

		void InitGL();
		void SetupShaders();
		void ResizeWindow(int Width, int Height);
		void Display();

		GLuint Buffers[1];
		GLuint VAOs[1];

		Panel* selectedPanel;

	private:
		Gui* gui;
		Panel windowPanel;
		GLFWwindow* window = nullptr;
		GLuint shaderProgram;

		GLfloat Width, Height;
		char* name = nullptr;
		bool visible = true;
};

#endif