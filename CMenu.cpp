#include "CMenu.h"

CMenu CMenu::menuController;

CMenu::CMenu()
{
    menuText = "";
    menuItems.clear();
    size = 0;
    type = -1;
}


void CMenu::buildMenu(std::string inText, std::vector<std::string> inItems, e_menuType inType)
{
    menuText = inText;
    menuItems = inItems;
    size = menuItems.size();
    type = inType;
    built = true;
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
}

void CMenu::onRender(SDL_Surface* dpy, int x, int y)
{
    // Render out the menu
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

int CMenu::handleClick(int xPos, int yPos)
{
    // Return which menu item was clicked on as a zero index int.
    if (type == e_cityMenu)
    {

    }
    if (type == e_convoMenu)
    {

    }
    return -1;
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
