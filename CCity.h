#ifndef _CCITY_H
#define _CCITY_H

#include <vector>
#include <SDL.h>
#include <string>

#include "CSurface.h"
#include "CCitizen.h"

class CCity
{
    private:
        SDL_Surface* cityView;
        std::vector<CCitizen*> citizens;
        std::vector<CCity*> neighbours;
        std::string cityName;
        e_cities nameEnum;
        int mapX;
        int mapY;

    public:
        CCity();
        bool onLoad(char* file);
        void onRender(SDL_Surface* dpy);
        void onCleanup();
        e_cities getNameEnum();
        int getMapX();
        int getMapY();
        int handleClick(int xPos, int yPos);
        std::string getCityName();
        std::vector<CCitizen*> getCitizenList();

};

#endif //CCITY_H
