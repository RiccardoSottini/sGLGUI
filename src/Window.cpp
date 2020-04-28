#include "Window.h"

Window::Window(Gui* gui, const GLfloat Width, const GLfloat Height, const char* name) {
	this->gui = gui;
	this->window = glfwCreateWindow(Width, Height, name, NULL, NULL);
	this->name = (char*) name;

	gui->windows.push_back(this);
	gui->glfw_windows[this->window] = this;

	InitGL();

	windowPanel.windowParent = this;
	windowPanel.panelParent = &windowPanel;

	addPanelQuad(&this->windowPanel.pQuad);
	windowPanel.updatePanel();

	setSize(Width, Height);
}

GLFWwindow* Window::getWindow() {
	return window;
}

Panel* Window::getWindowPanel() {
	return &windowPanel;
}

const bool Window::isVisible() {
	return visible;
}

void Window::setVisible(const bool visible) {
	this->visible = visible;
}

const std::array<GLfloat, 2> Window::getSize() {
	return std::array<GLfloat, 2> { this->getWidth(), this->getHeight() };
}

void Window::setSize(const GLfloat Width, const GLfloat Height) {
	this->Width = (Width >= minWidth) ? Width : minWidth;
	this->Height = (Height >= minHeight) ? Height : minHeight;

	glfwSetWindowSize(window, this->Width, this->Height);
	windowPanel.setSize(this->Width, this->Height, SIZE_PIXEL);

	ResizeWindow(this->Width, this->Height);
}

const GLfloat Window::getWidth() {
	return Width;
}

const GLfloat Window::getMinWidth() {
	return minWidth;
}

void Window::setWidth(const GLfloat Width) {
	this->Width = (Width >= minWidth) ? Width : minWidth;

	glfwSetWindowSize(window, this->Width, this->Height);
	windowPanel.setWidth(this->Width, SIZE_PIXEL);

	ResizeWindow(this->Width, this->Height);
}

void Window::setMinWidth(const GLfloat minWidth) {
	this->minWidth = minWidth;
	windowPanel.setMinWidth(this->minWidth, SIZE_PIXEL);

	if(this->minWidth > Width) setWidth(this->minWidth);

	glfwSetWindowSizeLimits(window, this->minWidth, this->minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

const GLfloat Window::getHeight() {
	return Height;
}

const GLfloat Window::getMinHeight() {
	return minHeight;
}

void Window::setHeight(const GLfloat Height) {
	this->Height = (Height >= minHeight) ? Height : minHeight;

	glfwSetWindowSize(window, this->Width, this->Height);
	windowPanel.setHeight(this->Height, SIZE_PIXEL);

	ResizeWindow(this->Width, this->Height);
}

void Window::setMinHeight(const GLfloat minHeight) {
	this->minHeight = minHeight;
	windowPanel.setMinHeight(this->minHeight, SIZE_PIXEL);

	if(this->minHeight > Height) setHeight(this->minHeight);

	glfwSetWindowSizeLimits(window, this->minWidth, this->minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void Window::addPanel(Panel* panel) {
	windowPanel.addPanel(panel);
}

void Window::addPanelQuad(PanelQuad* pQuad) {
	panelsQuad.push_back(pQuad);
	pQuad->n_quad = n_quads;
	updateVertices(n_quads++);
}

Panel* Window::getPanelClicked(Panel* panel, const GLfloat posX, const GLfloat posY) {
	for(int i = panel->list.size() - 1; i >= 0; i--) {
		Panel* selected = panel->list[i];

		if((posX >= selected->getPosX()) && (posX <= selected->getPosX() + selected->getWidth()) &&
	  	   (posY >= selected->getPosY()) && (posY <= selected->getPosY() + selected->getHeight())) {
			return getPanelClicked(selected, posX - selected->getPosX(), posY - selected->getPosY());
		}
	}

	return panel;
}

const char* vertexSource = R"glsl(
	#version 450 core

	layout(location = 0) uniform vec2 WindowSize;
	layout(location = 1) in vec2 vPosition;
	layout(location = 2) in vec4 vColor;

	out vec4 fs_color;

	void main() {
		fs_color = vColor;

		gl_Position[0] = (vPosition[0] / (WindowSize[0] / 2.0)) - 1;
		gl_Position[1] = 1 - (vPosition[1] / (WindowSize[1] / 2.0));
		gl_Position[2] = 0.0;
		gl_Position[3] = 1.0;
	}
)glsl";

const char* fragmentSource = R"glsl(
	#version 450 core

	layout(location = 0) out vec4 fColor;
	layout(location = 1) in vec4 fs_color;

	void main() {
		fColor = fs_color;
	}
)glsl";

void Window::InitGL() {
	glfwMakeContextCurrent(window);
	glewInit();
	SetupShaders();

	glCreateBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, MAX_PANELS * 24 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, VAOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

	glUniform2f(0, Width, Height);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (void(*)) (2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void Window::SetupShaders() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void Window::Display() {
	glfwMakeContextCurrent(window);

	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_QUADS, 0, n_quads * 8);

	glfwSwapBuffers(window);
}

void Window::ResizeWindow(int Width, int Height) {
	glfwMakeContextCurrent(window);

	glViewport(0, 0, Width, Height);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glUniform2f(0, Width, Height);

	//DISPLAY INSTRUCTIONS (Without calling Display Function)
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_QUADS, 0, n_quads * 8);

	glfwSwapBuffers(window);
}

void Window::updateVertices(int n_quad) {
	glfwMakeContextCurrent(window);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

	if(panelsQuad[n_quad]->visible) {
		GLfloat* color = panelsQuad[n_quad]->quadColor;
		std::array<GLfloat, 4> lines = panelsQuad[n_quad]->lines;

		std::vector<GLfloat> vertex = {
			lines[2], lines[0],
			lines[3], lines[0],
			lines[3], lines[1],
			lines[2], lines[1]
		};

		for(int v = 0; v < 4; v++) {
			GLfloat data[6] = {vertex[v*2], vertex[(v*2)+1], color[0], color[1], color[2], color[3]};
			glBufferSubData(GL_ARRAY_BUFFER, n_quad * sizeof(GLfloat) * 24 + (v * sizeof(data)), sizeof(data), &data);
		}
	} else {
		for(int v = 0; v < 4; v++) {
			GLfloat data[2] = {0.0, 0.0};
			glBufferSubData(GL_ARRAY_BUFFER, n_quad * sizeof(GLfloat) * 24 + (v * sizeof(GLfloat) * 6), sizeof(data), &data);
		}
	}
}