#include "Gui.h"
#include "Event.h"
#include "Window.h"

std::map<GLFWwindow*, Window*> Gui::glfw_windows;

Gui::Gui() {
    glfwInit();
    glewInit();
}

void Gui::EventLoop() {
    while(true) {
        glfwPollEvents();
        InputEvent inputEvent(this);

        for(int i = 0; i < windows.size(); i++) {
            glfwSwapBuffers(windows[i]->getWindow());

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

void Gui::Terminate() {
	glfwTerminate();
}