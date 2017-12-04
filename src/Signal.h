#ifndef SIGNAL_H
#define SIGNAL_H

#include "Gui.h"


/* TYPE */

#define INPUT_KEY         	   0
#define INPUT_CHAR         	   1
#define INPUT_CHARMODS     	   2
#define INPUT_CURSORPOS    	   3
#define INPUT_CURSORENTER      4
#define INPUT_MOUSEBUTTON      5
#define INPUT_SCROLL           6
#define INPUT_JOYSTICK         7
#define INPUT_DROP             8

#define WINDOW_CLOSE           9
#define WINDOW_SIZE           10
#define WINDOW_POS            11
#define WINDOW_ICONIFY        12
#define WINDOW_FOCUS          13
#define WINDOW_REFRESH        14
#define FRAMEBUFFER_SIZE      15

#define MONITOR_CONNECTED     16
#define MONITOR_DISCONNECTED  17


/* CURSORENTER */

#define INPUT_CURSOR_LEFT     0 
#define INPUT_CURSOR_ENTERED  1   

class Signal {
	public:
		Signal(const int type) 
			: type(type), signal(0), action(0) {
		}

		Signal(const int type, const int signal) 
			: type(type), signal(signal), action(0)  {
		}

		Signal(const int type, const int signal, const int action) 
			: type(type), signal(signal), action(action)  {
		}

		int type, signal, action; 
};

#endif