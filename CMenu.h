#ifndef _CMENU_H
#define _CMENU_H

#include <string>
#include <vector>

#include <SDL.h>

#include "Define.h"

class CMenu
{
    private:
        std::vector<std::string> menuItems;
        std::string menuText;
        int size;
        bool active;
        bool built;
        int type;

    public:
        static CMenu menuController;
        CMenu();
        void buildMenu(std::string menuText, std::vector<std::string> menuItems, e_menuType inType);
        void clearMenu();
        void onRender(SDL_Surface* dpy, int x, int y);
        void makeActive();
        bool isActive();
        bool isBuilt();

        int handleClick(int xPos, int yPos);
        void handleMove(int xPos, int yPos);
};

#endif //CMENU_H
