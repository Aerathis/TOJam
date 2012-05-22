#include "CInventory.h"

CInventory CInventory::inventoryControl;

CInventory::CInventory()
{
    itemList.clear();
}

void CInventory::addItem(s_inventoryItem* item)
{
    std::vector<s_inventoryItem*>::iterator it;
    bool found = false;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        if (found)
            break;
        s_inventoryItem* tempItem = *it;
        if (tempItem->name == item->name)
        {
            found = true;
            tempItem->quantity += 1;
        }
    }
    if (!found)
    {
        itemList.push_back(item);
    }
}

void CInventory::removeItem(s_inventoryItem* item)
{
    std::vector<s_inventoryItem*>::iterator it;
    bool found = false;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        if (found)
            break;
        s_inventoryItem* tempItem = *it;
        if (tempItem->name == item->name)
        {
            found = true;
            if (tempItem->quantity == 1)
                itemList.erase(it);
            else
                tempItem->quantity -= 1;
        }
    }
}

bool CInventory::onLoad()
{
    invPanel = CSurface::onLoad("./inventory.bmp");
    if (invPanel == NULL)
        return false;

    CSurface::transparent(invPanel,255,0,255);
    return true;
}

void CInventory::onRender(SDL_Surface* dpy)
{
    if (invPanel == NULL || dpy == NULL)
        return;
    CSurface::onDraw(dpy, invPanel, 900, 25);
}

void CInventory::buyItem(s_inventoryItem* item,int price)
{
    std::vector<s_inventoryItem*>::iterator it;
    bool found = false;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        if (found)
            break;
        s_inventoryItem* tempItem = *it;
        if (tempItem->name == item->name)
        {
            found = true;
            tempItem->quantity += 1;
        }
    }
    if (!found)
    {
        itemList.push_back(item);
    }
    CEntity* tempDude = CEntity::entityList[0];
    tempDude->getStatsPtr()->spendCash(price);
}

void CInventory::sellItem(s_inventoryItem* item, int price)
{

    std::vector<s_inventoryItem*>::iterator it;
    bool found = false;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        if (found)
            break;
        s_inventoryItem* tempItem = *it;
        if (tempItem->name == item->name)
        {
            found = true;
            if (tempItem->quantity == 1)
                itemList.erase(it);
            else
                tempItem->quantity -= 1;
        }
    }

    CEntity* tempDude = CEntity::entityList[0];
    tempDude->getStatsPtr()->gainCash(price);
}
