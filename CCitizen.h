#ifndef _CCITIZEN_H
#define _CCITIZEN_H

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "Define.h"

struct s_saleItem
{
    s_inventoryItem item;
    int price;
};

class CCitizen
{
    private:
        SDL_Surface* portrait;
        SDL_Surface* closeUp;
        std::vector<s_saleItem> wants;
        std::vector<s_saleItem> has;
        bool inConvo;

    public:
        CCitizen();

        bool onLoad(char* file);
        void onRender(SDL_Surface* dpy);
        void onCleanup();

        void sellWant(s_saleItem want);
        void buyHas(s_saleItem has, int quantity);

};

#endif //CCITIZEN_H
