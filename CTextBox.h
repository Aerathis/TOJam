#ifndef _CTEXTBOX_H
#define _CTEXTBOX_H

#include <string>

#include <SDL.h>

class CTextBox
{
    private:
        std::string text;

    public:
        static CTextBox textBoxController;

        CTextBox();
        void setText(std::string inText);
        void onRender(SDL_Surface* dpy, int x, int y);
};

#endif //CTEXTBOX_H
