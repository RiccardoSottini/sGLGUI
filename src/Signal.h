#ifndef SIGNAL_H
#define SIGNAL_H

#include "Gui.h"

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