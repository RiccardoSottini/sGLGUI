#include "Gui.h"
#include "Event.h"
#include "Window.h"

std::map<GLFWwindow*, Window*> Gui::glfw_windows;

Gui::Gui() {
}

void Gui::EventLoop() {
    while(true) {
        for(int i = 0; i < windows.size(); i++)
            glfwSwapBuffers(windows[i]->getWindow());

        glfwPollEvents();
    
        InputEvent inputEvent(this);

        for(int i = 0; i < windows.size(); i++) {
            glfwSetKeyCallback(windows[i]->getWindow(), inputEvent.KeyCallBack);
            glfwSetCharCallback(windows[i]->getWindow(), inputEvent.CharCallBack);
            glfwSetCursorPosCallback(windows[i]->getWindow(), inputEvent.CursorPosCallBack);
            glfwSetCursorEnterCallback(windows[i]->getWindow(), inputEvent.CursorEnterCallBack);
            glfwSetMouseButtonCallback(windows[i]->getWindow(), inputEvent.MouseButtonCallBack);
            glfwSetScrollCallback(windows[i]->getWindow(), inputEvent.ScrollCallBack);
        }

        inputEvent.getEvents();
    }
}
		
void Gui::Init() {
    glfwInit();
    glewInit();
}

void Gui::Terminate() {
	glfwTerminate();
}