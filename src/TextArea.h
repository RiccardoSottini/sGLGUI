#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "Panel.h"
#include "Window.h"

class TextArea : public Panel {
	public:
		TextArea();
		TextArea(Window* windowParent);
		TextArea(Panel* panelParent);

		void addChar(const char c);

		void removeChar();

		const std::string getText();

	private:
		std::string Text = "";
};

#endif