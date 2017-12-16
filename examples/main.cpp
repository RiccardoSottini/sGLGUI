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

	GLfloat fColorPanelBlue[4] = {0.0, 0.0, 1.0, 1.0};  // blue
	GLfloat fColorPanelWhite[4] = {1.0, 1.0, 1.0, 1.0};  // white
	GLfloat fColorPanelGreen[4] = {0.0, 1.0, 0.0, 1.0};  // green

	w.getWindowPanel()->setColor(fColorPanelBlue); //set Window 'w' background color to blue

	Panel p(&w);
	p.setSize(200, 200);
	p.setColor(fColorPanelWhite);

	Panel p2(&p);
	p2.setSize(100, 100);
	p2.setColor(fColorPanelGreen);

	Panel p3(&p2);
	p3.setSize(50, 50);
	p3.setColor(fColorPanelBlue);

	Panel p4(&p3);
	p4.setSize(25, 25);

	p.setPosition(300, 300);
	p2.setPosition(100, 100);
	p3.setPosition(50, 50);
	p4.setPosition(25, 25);

	gui.EventLoop();

	return 0;
}