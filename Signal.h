#ifndef SIGNAL_H
#define SIGNAL_H

#include "Gui.h"

/* EVENT */

#define WINDOW_EVENT          0
#define MONITOR_EVENT         1
#define INPUT_EVENT           2


/* TYPE */

#define WINDOW_NOEVENT       -1
#define WINDOW_CLOSE          0
#define WINDOW_SIZE           1
#define WINDOW_POS            2
#define WINDOW_ICONIFY        3
#define WINDOW_FOCUS          4
#define WINDOW_REFRESH        5
#define FRAMEBUFFER_SIZE      6

#define MONITOR_NOEVENT      -1
#define MONITOR_CONNECTED     0
#define MONITOR_DISCONNECTED  1

#define INPUT_NOEVENT        -1
#define INPUT_KEY         	  0
#define INPUT_CHAR         	  1
#define INPUT_CHARMODS     	  2
#define INPUT_CURSORPOS    	  3
#define INPUT_CURSORENTER     4
#define INPUT_MOUSEBUTTON     5
#define INPUT_SCROLL          6
#define INPUT_JOYSTICK        7
#define INPUT_DROP            8


/* CURSORENTER */

#define INPUT_CURSOR_LEFT     0 
#define INPUT_CURSOR_ENTERED  1   

class Signal {
	public:
		// MONITOR_EVENT
		Signal(const int event, const int type) 
			: event(event), type(type), signal(0), action(0) {
		}

		// WINDOW_EVENT
		Signal(const int event, const int type, const int signal) 
			: event(event), type(type), signal(signal), action(0)  {
		}

		//INPUT_EVENT
		Signal(const int event, const int type, const int signal, const int action) 
			: event(event), type(type), signal(signal), action(action)  {
		}

		int event, type, signal, action; 
};

#endif