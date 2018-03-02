#include "TextArea.h"

TextArea::TextArea() {
  this->type = TEXTAREA;
}

TextArea::TextArea(Window* windowParent) {
	this->windowParent = windowParent;
	this->windowParent->getWindowPanel()->addPanel(this);
	this->type = TEXTAREA;
}

TextArea::TextArea(Panel* panelParent) {
	this->panelParent = panelParent;
	this->panelParent->addPanel(this);
	this->type = TEXTAREA;
}

void TextArea::addChar(const char c) {
	Text += c;
	getText();
}

void TextArea::removeChar() {
	if(Text.size() > 0) 
		Text.pop_back();

	getText();
}

const std::string TextArea::getText() {
	std::cout << Text << '\n';
  
	return Text;
}