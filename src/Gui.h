#ifndef GUI_H
#define GUI_H

#include "Signal.h"
#include "def.h"

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <future>
#include <map>
#include <array>

class Event;
class Window;

class Gui {
	public:
		Gui();
		void EventLoop();
		void Init();
		void Terminate();

		template<class C, class S, typename SLOT> void connect(C Class, S Signal, SLOT slot()) {
			Class->slots[{Signal.type, Signal.signal, Signal.action}] = slot;

			std::cout << "Connect: " << Signal.type << "   " << Signal.signal << "   " << Signal.action << '\n';
		}

		static std::map<GLFWwindow*, Window*> glfw_windows;
		std::vector<Window*> windows;
		std::future<void> eventLoopThread;
};

#endif