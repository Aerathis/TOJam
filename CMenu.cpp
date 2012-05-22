#include "CMenu.h"

CMenu CMenu::menuController;

CMenu::CMenu()
{
    menuText = "";
    menuItems.clear();
    size = 0;
    type = -1;
    buy = true;
}


void CMenu::buildMenu(CCitizen* inSeller)
{
    seller = inSeller;
    built = true;
    buy = true;
    menuBuyBackground = CSurface::onLoad("./buy.bmp");
    menuSellBackground = CSurface::onLoad("./sell.bmp");
    CSurface::transparent(menuBuyBackground,255,0,255);
    CSurface::transparent(menuSellBackground,255,0,255);
}

void CMenu::clearMenus()
{
    menuText = "";
    doubleMenuText = "";
    menuItems.clear();
    doubleMenuItems.clear();
    size = 0;
    built = false;
    active = false;
    isDouble = false;
    type = -1;
    SDL_FreeSurface(menuBuyBackground);
    SDL_FreeSurface(menuSellBackground);
}

void CMenu::onRender(SDL_Surface* dpy, int x, int y)
{
    if (buy)
    {
        CSurface::onDraw(dpy, menuBuyBackground,20,326);

    }
    else
    {
        CSurface::onDraw(dpy, menuSellBackground,20,326);
    }
}

void CMenu::onRender(SDL_Surface* dpy, int x, int y, int x2, int y2)
{
    // Render out a double menu
}
void CMenu::makeActive()
{
    if (!active)
        active = true;
}

bool CMenu::isActive()
{
    return active;
}

bool CMenu::isBuilt()
{
    return built;
}

s_menuAction CMenu::handleClick(int xPos, int yPos)
{
    s_menuAction result;
    if (xPos > 780 && xPos < 830 &&
        yPos > 346 && yPos < 386)
        {
            result.selection = e_menuLeave;
            return result;
        }
    else if (xPos > 520 && xPos < 630 &&
             yPos > 326 && yPos < 386)
             {
                 if (!buy)
                    buy = true;
             }
    else if (xPos > 630 && xPos < 780 &&
             yPos > 326 && yPos < 386)
             {
                 if (buy)
                    buy = false;
             }
    else if (xPos > 50 && xPos < 100)
    {
        if (yPos > 406 && yPos < 456)
            {
                if (buy)
                {
                    result.selection = e_menuBuy;
                }
                else
                {
                    result.selection = e_menuSell;
                }
            }
    }
    result.selection = e_menuNone;
    return result;
}

void CMenu::handleMove(int xPos, int yPos)
{
    // Change the colour of the menu item being hovered over
}

bool CMenu::isDoubleMenu()
{
    return isDouble;
}

s_menuFormat CMenu::getMenuFormat()
{
    return selectionFormat;
}
