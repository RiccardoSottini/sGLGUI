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

		GLFWwindow* getWindow();
		Panel* getWindowPanel();

		/* Visibile */
		const bool isVisible();
		void setVisible(const bool visible);

		/* Size (Width + Height) */
		const std::array<GLfloat, 2> getSize();
		void setSize(const GLfloat Width, const GLfloat Height);

		/* Width */
		const GLfloat getWidth();
		const GLfloat getMinWidth();
		void setWidth(const GLfloat Width);
		void setMinWidth(const GLfloat minWidth);

		/* Height */
		const GLfloat getHeight();
		const GLfloat getMinHeight();
		void setHeight(const GLfloat Height);
		void setMinHeight(const GLfloat minHeight);

		/* Panel */
		void addPanel(Panel* panel);
		void addPanelQuad(PanelQuad* pQuad);
		Panel* getPanelClicked(Panel* panel, const GLfloat posX, const GLfloat posY);

		void InitGL();
		void SetupShaders();
		void Display();
		void ResizeWindow(int Width, int Height);
		void updateVertices(int n_quad);

		Panel* selectedPanel;
		std::vector<PanelQuad*> panelsQuad;

		std::map<std::array<int, 3>, void(*)()> slots;

		GLuint Buffers[1];
		GLuint VAOs[1];

	private:
		Gui* gui;
		Panel windowPanel;
		GLFWwindow* window = nullptr;
		GLuint shaderProgram;

		GLfloat Width = 0, Height = 0;
		GLfloat minWidth = 0, minHeight = 0;
		char* name = nullptr;
		bool visible = true;

		const int MAX_PANELS = 64; //64 panels
		int n_quads = 0;
};

#endif