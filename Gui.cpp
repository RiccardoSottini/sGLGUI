#include "Gui.h"
#include "Event.h"
#include "Window.h"

std::map<GLFWwindow*, Window*> Gui::glfw_windows;

Gui::Gui() {
}

void Gui::EventLoop() {
	while(true) {
		for(int i = 0; i < windows.size(); i++)
			glfwSwapBuffers(windows[i]->window);

    	glfwPollEvents();
    	
    	InputEvent inputEvent(this);

    	for(int i = 0; i < windows.size(); i++) {
    		glfwSetKeyCallback(windows[i]->window, inputEvent.KeyCallBack);
    		glfwSetCharCallback(windows[i]->window, inputEvent.CharCallBack);
    		glfwSetCursorPosCallback(windows[i]->window, inputEvent.CursorPosCallBack);
    		glfwSetCursorEnterCallback(windows[i]->window, inputEvent.CursorEnterCallBack);
    		glfwSetMouseButtonCallback(windows[i]->window, inputEvent.MouseButtonCallBack);
            glfwSetScrollCallback(windows[i]->window, inputEvent.ScrollCallBack);
    	}

        inputEvent.getEvents();
    }

    //glfwDestroyWindow(w->window);
}
		
void Gui::Init() {
	glfwInit();
    glewInit();
}

void Gui::Terminate() {
	glfwTerminate();
}