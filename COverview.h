#ifndef _COVERVIEW_H
#define _COVERVIEW_H

#include <vector>
#include <SDL.h>

#include "CSurface.h"
#include "CCity.h"

class COverview
{
    private:
        int height, width;
        SDL_Surface* overviewMap;

    public:
        static std::vector<CCity*> cityList;
        COverview();

        bool onLoad(char* file);
        void onRender(SDL_Surface* dpy);
        void onCleanup();

        static std::vector<CCity*> getCityList();

        e_cities handleClick(int xPos, int yPos);
        void handleMouseOver(int xPos, int yPos);
};

#endif //COVERVIEW_H
