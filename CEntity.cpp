#include "CEntity.h"

std::vector<CEntity*> CEntity::entityList;

CEntity::CEntity()
{
    entSurface = NULL;
    x = y = 0.0f;
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

void CEntity::onLoop()
{
    animController.onAnimate();
}

void CEntity::onRender(SDL_Surface* dpy)
{
    if (entSurface == NULL || dpy == NULL)
        return;
    CSurface::onDraw(dpy, entSurface, x, y, 0, 0, width, height);
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

void CEntity::sellToCitizen(s_saleItem item)
{
    currentConvo->sellWant(item);
    for (int i = 0; i < item.item.quantity; i++)
    {
        CInventory::inventoryControl.sellItem(&item.item, item.price);
    }
}

void CEntity::buyFromCitizen(s_saleItem item, int quantity)
{
    currentConvo->buyHas(item, quantity);
    for (int i = 0; i < quantity; i++)
    {
        CInventory::inventoryControl.buyItem(&item.item, item.price);
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

void CEntity::processEventResults(s_eventResult results)
{
    switch (results.type)
    {
        case e_moveToCity:
            break;
        case e_enterConvo:
            break;
        case e_leave:
            break;
        case e_buy:
            break;
        case e_sell:
            break;
        default:
            {}
    }
}
