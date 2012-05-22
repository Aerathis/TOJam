#ifndef _CINVENTORY_H
#define _CINVENTORY_H

#include <vector>
#include <string>
#include <SDL.h>

#include "CEntity.h"
#include "Define.h"

// Inventory panel width = 367 pixels

class CInventory
{
    private:
        std::vector<s_inventoryItem*> itemList;
        SDL_Surface* invPanel;

    public:

        static CInventory inventoryControl;

        CInventory();

        void addItem(s_inventoryItem* item);
        void removeItem(s_inventoryItem* item);
        bool onLoad();
        void onRender(SDL_Surface* dpy);
        void buyItem(s_inventoryItem* item, int price);
        void sellItem(s_inventoryItem* item, int price);


};

#endif //CINVENTORY_H
