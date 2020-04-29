#include "Gui.h"
#include "Window.h"
#include "TextArea.h"

#include <iostream>

GLfloat colorRed[4]	=	{ 1.0, 0.0, 0.0, 1.0 };	//rgba red color
GLfloat colorGreen[4] = { 0.0, 1.0, 0.0, 1.0 };	//rgba green color
GLfloat colorBlue[4] =	{ 0.0, 0.0, 1.0, 1.0 };	//rgba blue color
GLfloat colorBlack[4] = { 0.0, 0.0, 0.0, 1.0 };	//rgba black color
GLfloat colorWhite[4] = { 1.0, 1.0, 1.0, 1.0 };	//rgba white color

void e_key() { std::cout << "e_key\n"; }
void e_char() { std::cout << "e_char\n"; }
void e_cursorpos() { std::cout << "e_cursorpos\n"; }
void e_cursorenter() { std::cout << "e_cursorenter\n"; }
void e_mousebutton() { std::cout << "e_mousebutton\n"; }
void e_scroll() { std::cout << "e_scroll\n"; }

int main() {
	Gui *gui = new Gui();
	Window w(gui, 500, 500, "Window");

	//w.getWindowPanel()->setVisible(false); //set visible = false and catch no events on 'windowPanel' of 'w'

	gui->connect(&w, Signal(INPUT_KEY, KEY_E, PRESS), &e_key);
	gui->connect(&w, Signal(INPUT_CHAR, 'a'), &e_char);
	gui->connect(&w, Signal(INPUT_CURSOR_POS), &e_cursorpos);
	gui->connect(&w, Signal(INPUT_CURSOR_ENTER, INPUT_CURSOR_ENTERED), &e_cursorenter);
	gui->connect(&w, Signal(INPUT_MOUSE_BUTTON, MOUSE_BUTTON_LEFT, PRESS), &e_mousebutton);
	gui->connect(&w, Signal(INPUT_SCROLL), &e_scroll);

	std::array<Align, 4> vec_alignments = w.getWindowPanel()->getAlignments();
	for(int i = 0; i < vec_alignments.size(); i++)
		std::cout << "Alignment[" << i << "]: " << vec_alignments[i].offset << '\n';

	w.setMinWidth(200);
	w.setMinHeight(200);

	Panel p(&w);
	p.setPosition(10, 10, SIZE_PERCENT);
	p.setSize(80, 80, SIZE_PERCENT);
	p.setMinHeight(300, SIZE_PIXEL);
	p.setMinWidth(400, SIZE_PIXEL);
	p.setColor(colorRed);

	Panel p2(&p);
	p2.setAlign(ALIGN_RIGHT, 50, SIZE_PIXEL);
	p2.setSize(50, 50, SIZE_PERCENT);
	p2.setColor(colorGreen);

	Panel p3(&p);
	p3.setAlign(ALIGN_BOTTOM, 0, SIZE_PIXEL);
	p3.setSize(50, 50, SIZE_PERCENT);
	p3.setPosX(50, SIZE_PIXEL);
	p3.setMinHeight(150, SIZE_PIXEL);
	p3.setColor(colorBlue);

	Panel p4(&p2);
	p4.setAlign(ALIGN_BOTTOM, 10, SIZE_PERCENT);
	p4.setAlign(ALIGN_RIGHT, 10, SIZE_PERCENT);
	p4.setSize(80, 80, SIZE_PERCENT);
	p4.setColor("#6767ff");

	Panel p5(&p4);
	p5.setAlign(ALIGN_BOTTOM, 0, SIZE_PIXEL);
	p5.setAlign(ALIGN_RIGHT, 0, SIZE_PIXEL);
	p5.setSize(50, 50, SIZE_PIXEL);
	p5.setColor(colorBlack);

	gui->EventLoop();

	return 0;
}