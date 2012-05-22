#ifndef _CCITIZEN_H
#define _CCITIZEN_H

#include <SDL.h>
#include <string>
#include <vector>

#include "CSurface.h"
#include "Define.h"

class CCitizen
{
    private:
        SDL_Surface* portrait;
        SDL_Surface* closeUp;
        std::vector<s_saleItem> wants;
        std::vector<s_saleItem*> has;
        bool inConvo;
        std::string name;
        std::string description;

    public:
        CCitizen();

        bool onLoad(char* file);
        void onRender(SDL_Surface* dpy, int x, int y);
        void onCleanup();
        std::vector<s_saleItem*> getHas();

        void sellWant(s_saleItem want);
        void buyHas(s_saleItem has, int quantity);

};

#endif //CCITIZEN_H
