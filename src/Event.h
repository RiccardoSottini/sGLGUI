#ifndef EVENT_H
#define EVENT_H

#include "Window.h"
#include "Panel.h"
#include "Gui.h"

class Gui;

class InputEvent {
	public:
		InputEvent(Gui* gui);

		template<class C, typename V = std::map<int, std::array<int, 3>>::iterator> void execSlot(C Class, V value);

		void getEvents();
		static void setEvent(GLFWwindow* window, const int type, const int signal, const int action);

		static void KeyCallBack(GLFWwindow* window, int key, int scancode, int align, int mods);
		static void CharCallBack(GLFWwindow* window, unsigned int codepoint);
		static void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
		static void CursorEnterCallBack(GLFWwindow* window, int entered);
		static void MouseButtonCallBack(GLFWwindow* window, int button, int align, int mods);
		static void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
		static void WindowSizeCallBack(GLFWwindow* window, int width, int height);

		Gui* gui;

		static int n_events;
		static std::map<int, GLFWwindow*> ev_window; 
		static std::map<int, std::array<int, 3>> events;
		static std::map<int, std::array<GLdouble, 2>> pos;
		static std::map<int, std::array<GLdouble, 2>> size;
};

#endif