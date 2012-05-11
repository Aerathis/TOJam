#ifndef _COVERVIEW_H
#define _COVERVIEW_H

#include <vector>
#include <SDL.h>

#include "CSurface.h"
#include "CCity.h"

class COverview
{
    private:
        std::vector<CCity*> cityList;
        int height, width;
        SDL_Surface* overviewMap;

    public:
        COverview();

        bool onLoad(char* file);
        void onRender(SDL_Surface* dpy);
        void onCleanup();

        int handleClick(int xPos, int yPos);
};

#endif //COVERVIEW_H
