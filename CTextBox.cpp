#include "CTextBox.h"

CTextBox CTextBox::textBoxController;

CTextBox::CTextBox()
{
    text = "";
}

void CTextBox::setText(std::string inText)
{
    text = inText;
}

void CTextBox::onRender(SDL_Surface* dpy, int x, int y)
{

}
