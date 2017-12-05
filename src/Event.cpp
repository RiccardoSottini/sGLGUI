#include "Event.h"

GLFWwindow* InputEvent::current_window;
int InputEvent::n_events = 0;
std::map<int, std::array<int, 3>>InputEvent::events;
std::map<int, std::array<GLdouble, 2>> InputEvent::pos;

InputEvent::InputEvent(Gui* gui) : gui(gui) {
}

void InputEvent::getEvents() {
	for(int n_ev = 0; n_ev < n_events; n_ev++) {
		auto value = events.find(n_ev);
		if(value != events.end()) {
			switch(value->second[0]) {
				case INPUT_KEY:
					execSlot(gui->glfw_windows[current_window], n_ev);
					std::cout << "INPUT_KEY: " << value->second[1] << "   " << value->second[2] << '\n';
					break;
				case INPUT_CHAR:
					execSlot(gui->glfw_windows[current_window], n_ev);
					std::cout << "INPUT_CHAR: " << value->second[1] << '\n';
					break;
				case INPUT_CURSOR_POS:
					execSlot(gui->glfw_windows[current_window]->getPanelClicked(&gui->glfw_windows[current_window]->windowPanel, pos[n_ev][0], pos[n_ev][1]), n_ev);
					std::cout << "INPUT_CURSOR_POS: " << pos[n_ev][0] << "   " << pos[n_ev][1] << '\n';
					break;
				case INPUT_CURSOR_ENTER:
					execSlot(gui->glfw_windows[current_window], n_ev);
					std::cout << "INPUT_CURSOR_ENTER: " << value->second[1] << '\n';
					break;
				case INPUT_MOUSE_BUTTON:
					execSlot(gui->glfw_windows[current_window]->getPanelClicked(&gui->glfw_windows[current_window]->windowPanel, pos[n_ev][0], pos[n_ev][1]), n_ev);
					std::cout << "INPUT_MOUSE_BUTTON: " << pos[n_ev][0] << "   " << pos[n_ev][1] << "   " << value->second[1] << "   " << value->second[2] << '\n';
					break;
				case INPUT_SCROLL:
					execSlot(gui->glfw_windows[current_window], n_ev);
					std::cout << "INPUT_SCROLL: " << pos[n_ev][0] << "   " << pos[n_ev][1] << '\n';
					break;
				default:
					break;
			}
		}
	}

	if(n_events) std::cout << "N_EVENTS: " << n_events << "  -----------------------------\n";
	events.clear();
	n_events = 0;
}

void InputEvent::setEvent(GLFWwindow* window, const int type, const int signal, const int action) {
	current_window = window;
	std::array<int, 3> value = {type, signal, action};
	events[n_events++] = value;
}

void InputEvent::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	setEvent(window, INPUT_KEY, key, action);
}

void InputEvent::CharCallBack(GLFWwindow* window, unsigned int codepoint) {
	setEvent(window, INPUT_CHAR, codepoint, 0);
}

void InputEvent::CursorPosCallBack(GLFWwindow* window, double xpos, double ypos) {
	pos[n_events][0] = xpos, pos[n_events][1] = ypos;

	setEvent(window, INPUT_CURSOR_POS, 0, 0);
}

void InputEvent::CursorEnterCallBack(GLFWwindow* window, int entered) {
	setEvent(window, INPUT_CURSOR_ENTER, entered, 0);
}

void InputEvent::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
	glfwGetCursorPos(window, &pos[n_events][0], &pos[n_events][1]);

	setEvent(window, INPUT_MOUSE_BUTTON, button, action);
}

void InputEvent::ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
	pos[n_events][0] = xoffset, pos[n_events][1] = yoffset;

	setEvent(window, INPUT_SCROLL, 0, 0);
}