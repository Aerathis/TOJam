#include "CEntity.h"

#include <iostream>

std::vector<CEntity*> CEntity::entityList;

CEntity::CEntity()
{
    entSurface = NULL;
    location = NULL;
    x = 85;
    y = 637;
    width = height = 0;
}

CEntity::~CEntity()
{
}

bool CEntity::onLoad(char* file, int width, int height, int maxFrames)
{
    if ((entSurface = CSurface::onLoad(file)) == NULL)
    {
        return false;
    }

    CSurface::transparent(entSurface, 255,0,255);

    this->width = width;
    this->height = height;

    animController.maxFrames = maxFrames;

    return true;
}

void CEntity::onLoop(e_currentView* view)
{
    if (location)
    {
        if (x != location->getMapX() && y != location->getMapY())
        {
            int dy = y - location->getMapY();
            int dx = x - location->getMapX();
            if (dx == 0 || dy == 0)
            {
                x = location->getMapX();
                y = location->getMapY();
            }
            else
            {
                float deg = atan(dy/dx);
                x += cos(deg);
                y += sin(deg);
            }
        }
        if (x == location->getMapX() && y == location->getMapY())
        {
            *view = e_city;
        }
    }
}

void CEntity::onRender(SDL_Surface* dpy)
{
    if (entSurface == NULL || dpy == NULL)
        return;
    CSurface::onDraw(dpy, entSurface, x-50, y-50);
}

void CEntity::onCleanup()
{
    if (entSurface)
    {
        SDL_FreeSurface(entSurface);
    }

    entSurface = NULL;
}

CStats* CEntity::getStatsPtr()
{
    return &playerStats;
}

CCity* CEntity::getCurrentLocation()
{
    return location;
}

CCitizen* CEntity::getCurrentConvo()
{
    return currentConvo;
}

void CEntity::sellToCitizen(s_saleItem item)
{
    currentConvo->sellWant(item);
    for (int i = 0; i < item.item.quantity; i++)
    {
        CInventory::inventoryControl.sellItem(&item.item, item.buyPrice);
    }
}

void CEntity::buyFromCitizen(s_saleItem item, int quantity)
{
    currentConvo->buyHas(item, quantity);
    for (int i = 0; i < quantity; i++)
    {
        CInventory::inventoryControl.buyItem(&item.item, item.salePrice);
    }
    if (item.item.name == "gas")
    {
        for (int j = 0; j < quantity; j++)
        {
            CInventory::inventoryControl.removeItem(&item.item);
            playerStats.getGas(1);
        }
    }
}

void CEntity::processEventResults(s_eventResult results, e_currentView* view)
{
    switch (results.type)
    {
        case e_moveToCity:
            {
                location = parseCity(results.citySelection);
            }
            break;
        case e_enterConvo:
            {
                *view = e_convo;
            }
            break;
        case e_leave:
            {
                if (results.view == e_convo)
                {
                    *view = e_city;
                }
                else if (results.view == e_city)
                {
                    *view = e_overView;
                }
            }
            break;
        case e_buy:
            break;
        case e_sell:
            break;
        default:
            {}
    }
}

CCity* CEntity::parseCity(e_cities nameEnum)
{
    std::vector<CCity*> cities = COverview::cityList;
    std::vector<CCity*>::iterator it;
    bool found = false;
    CCity* result = NULL;
    for (it = cities.begin(); it != cities.end(); ++it)
    {
        if (found)
            break;
        CCity* temp = *it;
        if (temp->getNameEnum() == nameEnum)
        {
            found = true;
            result = *it;
        }
    }
    return result;
}
