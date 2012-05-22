#include "CItem.h"

std::vector<CItem*> CItem::itemList;

bool CItem::onLoad(char* file)
{
    itemList.clear();

    FILE* fileHandle = fopen(file,"r");
    int numItems;
    fscanf(fileHandle,"%d\n",&numItems);
    for (int i = 0; i < numItems; i++)
    {
        CItem* temp = new CItem();
        char itemName[80];
        char textImageFile[80];
        fscanf(fileHandle,"%[^,],%s\n",itemName,textImageFile);
        temp->name = itemName;
        temp->itemText = CSurface::onLoad(textImageFile);
        CSurface::transparent(temp->itemText,255,0,255);
        itemList.push_back(temp);
    }
    return true;
}

void CItem::onRender(SDL_Surface* dpy, int x, int y)
{
    CSurface::onDraw(dpy, itemImage, x, y);
    CSurface::onDraw(dpy, itemText, x + 50, y);
}

CItem* CItem::findItemByName(std::string itemName)
{
    std::vector<CItem*>::iterator it;
    bool found = false;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        if (found)
            break;
        CItem* testItem = *it;
        if (testItem->name == itemName)
        {
            return testItem;
        }
    }
    return NULL;
}
