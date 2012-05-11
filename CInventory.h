#ifndef _CINVENTORY_H
#define _CINVENTORY_H

#include <vector>
#include <string>

#include "CEntity.h"
#include "Define.h"

class CInventory
{
    private:
        std::vector<s_inventoryItem*> itemList;

    public:

        static CInventory inventoryControl;

        CInventory();

        void addItem(s_inventoryItem* item);
        void removeItem(s_inventoryItem* item);
        void buyItem(s_inventoryItem* item, int price);
        void sellItem(s_inventoryItem* item, int price);


};

#endif //CINVENTORY_H
