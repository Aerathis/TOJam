#include "CCitizen.h"

CCitizen::CCitizen()
{
    portrait = NULL;
    closeUp = NULL;
    inConvo = false;
    has.clear();
}

bool CCitizen::onLoad(char* file)
{
    wants.clear();
    has.clear();

    FILE* fileHandle = fopen(file,"r");
    if (fileHandle == NULL)
        return false;
    char names[80];
    fscanf(fileHandle,"%s\n",names);
    name = names;
    char descr[255];
    fscanf(fileHandle, "%[^\n]",descr);
    char portraitFile[80];
    fscanf(fileHandle, "%s\n",portraitFile);
    portrait = CSurface::onLoad(portraitFile);
    CSurface::transparent(portrait,255,0,255);
    int numHaves;
    fscanf(fileHandle,"%d,\n",&numHaves);
    for (int i = 0; i < numHaves; i++)
    {
        char itemName[80];
        int quantity;
        int buyPrice;
        int sellPrice;
        fscanf(fileHandle,"%s,%d,%d,%d\n",itemName,&quantity,&buyPrice,&sellPrice);
        s_inventoryItem* tempInv = new s_inventoryItem;
        s_saleItem* tempItem = new s_saleItem;
        tempInv->name = itemName;
        tempInv->quantity = quantity;
        tempInv->value = 0;
        tempItem->item = tempInv;
        tempItem->buyPrice = buyPrice;
        tempItem->salePrice = sellPrice;
        has.push_back(tempItem);
    }
    fclose(fileHandle);
    return true;
}

void CCitizen::onRender(SDL_Surface* dpy, int x, int y)
{
    if (dpy == NULL || portrait == NULL || closeUp || NULL)
        return;
    if (inConvo)
    {
        CSurface::onDraw(dpy, closeUp, 550, 100);
    }
    else
    {
        CSurface::onDraw(dpy, portrait, x, y);
    }
}

void CCitizen::buyHas(s_saleItem item, int quantity)
{
    std::vector<s_saleItem*>::iterator it;
    bool found = false;
    for (it = has.begin(); it != has.end(); ++it)
    {
        if (found)
            break;
        s_saleItem* tempItem = *it;
        if (tempItem->item->name == item.item->name)
        {
            found = true;
            if (quantity > tempItem->item->quantity)
            {
                quantity = tempItem->item->quantity;
            }
            tempItem->item->quantity -= quantity;
        }
    }
}

void CCitizen::sellWant(s_saleItem item)
{
    std::vector<s_saleItem>::iterator it;
    bool found = false;
    for (it = wants.begin(); it != wants.end(); ++it)
    {
        if (found)
            break;
        s_saleItem* tempItem = &*it;
        if (tempItem->item->name == item.item->name)
        {
            found = true;
            tempItem->item->quantity += item.item->quantity;
        }
    }
}

void CCitizen::onCleanup()
{
    if (portrait)
    {
        SDL_FreeSurface(portrait);
    }
    if (closeUp)
    {
        SDL_FreeSurface(closeUp);
    }
    portrait = NULL;
    closeUp = NULL;
}

std::vector<s_saleItem*> CCitizen::getHas()
{
    return has;
}
