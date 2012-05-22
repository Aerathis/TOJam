#ifndef _CITEM_H
#define _CITEM_H

#include <string>
#include <vector>

#include <SDL.h>

#include "CSurface.h"

class CItem
{
    private:
        SDL_Surface* itemImage;
        SDL_Surface* itemText;
        std::string name;

    public:
        static std::vector<CItem*> itemList;

        static bool onLoad(char* file);
        void onRender(SDL_Surface* dpy,int x, int y);
        static CItem* findItemByName(std::string itemName);

};

#endif //CITEM_H
