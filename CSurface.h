#ifndef _CSURFACE_H
#define _CSURFACE_H

#include <string>

#include <SDL.h>

class CSurface
{
    public:
        CSurface();

        static SDL_Surface* onLoad(char* file);

        static bool onDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
        static bool onDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h);

        static bool transparent(SDL_Surface* dest, int r, int g, int b);
};

#endif //CSURFACE_H
