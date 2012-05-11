#include "CCitizen.h"

CCitizen::CCitizen()
{
    portrait = NULL;
    closeUp = NULL;
    inConvo = false;
    wants.clear();
    has.clear();
}

bool CCitizen::onLoad(char* file)
{
    wants.clear();
    has.clear();

    FILE* fileHandle = fopen(file,"r");
    if (fileHandle == NULL)
        return false;
    char name[80];
    fscanf(fileHandle,"%s\n",name);
    int numHaves;
    fscanf(fileHandle,"%d,\n",&numHaves);
    for (int i = 0; i < numHaves; i++)
    {
        char itemName[80];
        int quantity;
        int price;
        fscanf(fileHandle,"%s,%d,%d\n",itemName,&quantity,&price);
    }
    return true;
}

void CCitizen::onRender(SDL_Surface* dpy)
{
    if (dpy == NULL || portrait == NULL || closeUp || NULL)
        return;
    if (inConvo)
    {
        CSurface::onDraw(dpy, closeUp, 320, 0);
    }
    else
    {
        CSurface::onDraw(dpy, portrait, 0, 0);
    }
}

void CCitizen::buyHas(s_saleItem item, int quantity)
{
    std::vector<s_saleItem>::iterator it;
    bool found = false;
    for (it = has.begin(); it != has.end(); ++it)
    {
        if (found)
            break;
        s_saleItem* tempItem = &*it;
        if (tempItem->item.name == item.item.name)
        {
            found = true;
            if (quantity > tempItem->item.quantity)
            {
                quantity = tempItem->item.quantity;
            }
            tempItem->item.quantity -= quantity;
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
        if (tempItem->item.name == item.item.name)
        {
            found = true;
            tempItem->item.quantity += item.item.quantity;
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
