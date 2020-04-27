#include "Gui.h"
#include "Event.h"

std::map<GLFWwindow*, Window*> Gui::glfw_windows;

Gui::Gui() {
    glfwInit();
}

void Gui::EventLoop() {
	auto WindowSizeCallBack = [](GLFWwindow* window, int Width, int Height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))->setSize(Width, Height);
	};

    while(true) {
        glfwPollEvents();
        //InputEvent inputEvent(this);

        for(int i = 0; i < windows.size(); i++) {
            /*int width, height, offsetWidth, offsetHeight;
            glfwGetWindowSize(windows[i]->getWindow(), &width, &height);
            offsetWidth = width - windows[i]->getWidth();
            offsetHeight = height - windows[i]->getHeight();

            if(offsetWidth || offsetHeight)
                windows[i]->ResizeWindow(offsetWidth, offsetHeight);*/

			windows[i]->Display();

            /*glfwSetKeyCallback(windows[i]->getWindow(), inputEvent.KeyCallBack);
            glfwSetCharCallback(windows[i]->getWindow(), inputEvent.CharCallBack);
            glfwSetCursorPosCallback(windows[i]->getWindow(), inputEvent.CursorPosCallBack);
            glfwSetCursorEnterCallback(windows[i]->getWindow(), inputEvent.CursorEnterCallBack);
            glfwSetMouseButtonCallback(windows[i]->getWindow(), inputEvent.MouseButtonCallBack);
            glfwSetScrollCallback(windows[i]->getWindow(), inputEvent.ScrollCallBack);*/

			glfwSetWindowUserPointer(windows[i]->getWindow(), windows[i]);
			glfwSetWindowSizeCallback(windows[i]->getWindow(), WindowSizeCallBack);
        }

        //inputEvent.getEvents();
    }
}

void Gui::Terminate() {
	glfwTerminate();
}