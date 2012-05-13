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
        std::vector<std::string> doubleMenuItems;
        std::string menuText;
        std::string doubleMenuText;
        int size;
        bool active;
        bool built;
        bool isDouble;
        int type;
        s_menuFormat selectionFormat;

    public:
        static CMenu menuController;
        CMenu();
        void buildMenu(std::string menuText, std::vector<std::string> menuItems, e_menuType inType);
        void buildSecondMenu(std::string menuText, std::vector<std::string> menuItems, e_menuType inType);
        void clearMenus();
        void onRender(SDL_Surface* dpy, int x, int y);
        void onRender(SDL_Surface* dpy, int x, int y, int x2, int y2);
        void makeActive();
        bool isActive();
        bool isBuilt();
        bool isDoubleMenu();
        s_menuFormat getMenuFormat();

        int handleClick(int xPos, int yPos);
        void handleMove(int xPos, int yPos);
};

#endif //CMENU_H
