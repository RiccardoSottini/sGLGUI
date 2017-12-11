#include "Gui.h"
#include "Window.h"

#include <iostream>

void e_key() { std::cout << "e_key\n"; }
void e_char() { std::cout << "e_char\n"; }
void e_cursorpos() { std::cout << "e_cursorpos\n"; }
void e_cursorenter() { std::cout << "e_cursorenter\n"; }
void e_mousebutton() { std::cout << "e_mousebutton\n"; }
void e_scroll() { std::cout << "e_scroll\n"; }

int main() {
	Gui gui;
	
	Window w(&gui, 500, 500, "Window");
	Window w2(&gui, 300, 300, "Window2");

	//w.getWindowPanel()->setVisible(false); //set visible = false and catch no events on 'windowPanel' of 'w'

	gui.connect(&w, Signal(INPUT_KEY, KEY_E, PRESS), &e_key);
	gui.connect(&w, Signal(INPUT_CHAR, 'a'), &e_char);
	gui.connect(w.getWindowPanel(), Signal(INPUT_CURSOR_POS), &e_cursorpos);
	gui.connect(&w, Signal(INPUT_CURSOR_ENTER, INPUT_CURSOR_ENTERED), &e_cursorenter);
	gui.connect(w.getWindowPanel(), Signal(INPUT_MOUSE_BUTTON, MOUSE_BUTTON_LEFT, PRESS), &e_mousebutton);
	gui.connect(&w, Signal(INPUT_SCROLL), &e_scroll);


	w.getWindowPanel()->addAlignment(Align(ALIGN_RIGHT, 10)); //add an alignment (2, 10)

	std::vector<Align> vec_alignments = w.getWindowPanel()->getAlignments();
	for(int i = 0; i < vec_alignments.size(); i++)
		std::cout << "Alignment[" << i << "]: " << vec_alignments[i].alignment << "   " << vec_alignments[i].offset << '\n';

	GLfloat fColorWindowPanel[4] = {0.0, 0.0, 1.0, 1.0};  // blue
	w.getWindowPanel()->setColor(fColorWindowPanel); //set Window 'w' background color to blue

	Panel p;
	p.setSize(200, 200);
	p.setPosition(100, 100);

	GLfloat fColorPanel[4] = {1.0, 1.0, 1.0, 1.0};  // white
	p.setColor(fColorPanel);
	w.addPanel(&p);

	Panel p2;
	p2.setSize(50, 50);
	p2.setPosition(175, 175);
	p.addPanel(&p2);

	p2.setVisible(false);

	gui.EventLoop();

	return 0;
}