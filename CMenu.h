#ifndef _CMENU_H
#define _CMENU_H

#include <string>
#include <vector>

#include <SDL.h>

#include "CCitizen.h"
#include "CItem.h"
#include "CSurface.h"
#include "Define.h"

class CMenu
{
    private:
        std::vector<std::string> menuItems;
        std::vector<std::string> doubleMenuItems;
        std::string menuText;
        std::string doubleMenuText;
        SDL_Surface* menuBuyBackground;
        SDL_Surface* menuSellBackground;
        bool buy;
        int size;
        bool active;
        bool built;
        bool isDouble;
        int type;
        s_menuFormat selectionFormat;
        CCitizen* seller;

    public:
        static CMenu menuController;
        CMenu();
        void buildMenu(CCitizen* seller);
        void clearMenus();
        void onRender(SDL_Surface* dpy, int x, int y);
        void onRender(SDL_Surface* dpy, int x, int y, int x2, int y2);
        void makeActive();
        bool isActive();
        bool isBuilt();
        bool isDoubleMenu();
        s_menuFormat getMenuFormat();

        s_menuAction handleClick(int xPos, int yPos);
        void handleMove(int xPos, int yPos);
};

#endif //CMENU_H
