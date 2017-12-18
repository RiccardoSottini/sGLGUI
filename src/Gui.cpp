#include "Gui.h"
#include "Event.h"

std::map<GLFWwindow*, Window*> Gui::glfw_windows;

Gui::Gui() {
    glfwInit();
}

void Gui::EventLoop() {
    while(true) {
        glfwPollEvents();
        InputEvent inputEvent(this);

        for(int i = 0; i < windows.size(); i++) {
            int width, height, offsetWidth, offsetHeight;
            glfwGetWindowSize(windows[i]->getWindow(), &width, &height);
            offsetWidth = width - windows[i]->getWidth();
            offsetHeight = height - windows[i]->getHeight();

            if(offsetWidth || offsetHeight)
                windows[i]->ResizeWindow(offsetWidth, offsetHeight);

            windows[i]->Display();
            glfwSwapBuffers(windows[i]->getWindow());

            glfwSetKeyCallback(windows[i]->getWindow(), inputEvent.KeyCallBack);
            glfwSetCharCallback(windows[i]->getWindow(), inputEvent.CharCallBack);
            glfwSetCursorPosCallback(windows[i]->getWindow(), inputEvent.CursorPosCallBack);
            glfwSetCursorEnterCallback(windows[i]->getWindow(), inputEvent.CursorEnterCallBack);
            glfwSetMouseButtonCallback(windows[i]->getWindow(), inputEvent.MouseButtonCallBack);
            glfwSetScrollCallback(windows[i]->getWindow(), inputEvent.ScrollCallBack);

            glfwSetWindowSizeCallback(windows[i]->getWindow(), inputEvent.WindowSizeCallBack);
        }

        inputEvent.getEvents();
    }
}

void Gui::Terminate() {
	glfwTerminate();
}