#include "Window.h"

Window::Window(Gui* gui, const double Width, const double Height, const char* name) {
	this->gui = gui;
	this->window = glfwCreateWindow(Width, Height, name, NULL, NULL);
	setSize(Width, Height);
	this->name = (char*) name;

	gui->windows.push_back(this);
	gui->glfw_windows[this->window] = this;

	InitGL();

	this->windowPanel.windowParent = this;
	this->windowPanel.panelParent = &this->windowPanel;
	addPanelQuad(&this->windowPanel.pQuad);
}

void Window::setSize(const double Width, const double Height) {
	this->Width = Width;
	this->Height = Height;

	this->windowPanel.setSize(Width, Height);
}

void Window::setVisible(const bool visible) {
	this->visible = visible;
}

void Window::addPanel(Panel* panel) {
    this->windowPanel.addPanel(panel);
}

GLFWwindow* Window::getWindow() {
	return this->window;
}

Panel* Window::getWindowPanel() {
	return &windowPanel;
}

Panel* Window::getPanelClicked(Panel* panel, const double posX, const double posY) {
	for(int i = panel->list.size() - 1; i >= 0; i--) {
		Panel* selected = panel->list[i];

		if((posX >= selected->getPosX()) && (posX <= selected->getPosX() + selected->getWidth()) &&
	  	   (posY >= selected->getPosY()) && (posY <= selected->getPosY() + selected->getHeight())) {
			return getPanelClicked(selected, posX - selected->getPosX(), posY - selected->getPosY());
		}
	}

	return panel;
}

const GLdouble Window::getWidth() {
	return Width;
}

const GLdouble Window::getHeight() {
	return Height;
}

const bool Window::isVisible() {
	return visible;
}

const char* vertexSource = R"glsl(
	#version 450 core

	layout(location = 0) uniform vec2 WindowSize;
	layout(location = 1) in vec4 vPosition;
	layout(location = 2) in vec4 vColor;

	out vec4 fs_color;

	void main() {
		fs_color = vColor;
		gl_Position = vec4(vPosition[0] / (WindowSize[0] / 2.0) - 1, 1 - (vPosition[1] / (WindowSize[1] / 2.0)), 0.0, 1.0);
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

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (void (*)) (2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void Window::addPanelQuad(PanelQuad* pQuad) {
	panelsQuad.push_back(pQuad);
	pQuad->n_quad = n_quads;
	updateVertices(n_quads++);
}

void Window::updateVertices(int n_quad) {
	glfwMakeContextCurrent(window);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

	if(panelsQuad[n_quad]->visible) {
		GLdouble* size = panelsQuad[n_quad]->quadSize;
		GLdouble* pos = panelsQuad[n_quad]->quadPos;
		GLfloat* color = panelsQuad[n_quad]->quadColor;

		std::vector<GLfloat> data = {
			pos[0], pos[1],
			pos[0] + size[0], pos[1],
			pos[0] + size[0], pos[1] + size[1],
			pos[0], pos[1] + size[1]
		};

		for(int v = 0; v < 4; v++) {
			GLfloat vertex[6] = {data[v*2], data[(v*2)+1], color[0], color[1], color[2], color[3]};
			glBufferSubData(GL_ARRAY_BUFFER, n_quad * sizeof(GLfloat) * 24 + (v * sizeof(vertex)), sizeof(vertex), &vertex);
		}
	} else {
		// Clear PanelQuad
		for(int v = 0; v < 4; v++) {
			GLfloat vertex[2] = {0.0, 0.0};
			glBufferSubData(GL_ARRAY_BUFFER, n_quad * sizeof(GLfloat) * 24 + (v * sizeof(GLfloat) * 6), sizeof(vertex), &vertex);
		}
	}
}

void Window::ResizeWindow(int offset_width, int offset_height) {
	glfwMakeContextCurrent(window);

	setSize(Width + offset_width, Height + offset_height);

	glViewport(0, 0, Width, Height);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glUniform2f(0, Width, Height);
}

void Window::Display() {
	glfwMakeContextCurrent(window);

	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_QUADS, 0, n_quads * 8);
}