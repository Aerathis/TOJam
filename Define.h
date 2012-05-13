#ifndef _DEFINE_H
#define _DEFINE_H

#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define TILE_SIZE 16
#define WWIDTH 1280
#define WHEIGHT 720
#define PORTRAITWIDTH 100
#define MENUITEMWIDTH 50

#include <string>

class CCitizen;

enum e_currentView
{
    e_overView,
    e_city,
    e_convo,
    e_results,
    e_other
};

enum e_resultType
{
    e_buy,
    e_sell,
    e_leave,
    e_enterConvo,
    e_moveToCity
};

enum e_menuType
{
    e_cityMenu = 0,
    e_convoMenu
};

enum e_menuSelection
{
    e_menuBuy,
    e_menuSell,
    e_menuLeave,
    e_startConvo
};

struct s_inventoryItem
{
    std::string name;
    int value;
    int quantity;
};

struct s_saleItem
{
    s_inventoryItem item;
    int buyPrice;
    int salePrice;
};

struct s_menuAction
{
    e_menuSelection selection;
    s_saleItem item;
    CCitizen* convoTarget;
};

enum e_cities
{
    e_first = 0,
    e_second,
    e_third,
    e_fourth,
    e_fifth,
    e_home
};

struct s_item
{
    std::string name;
    int value;
};

struct s_menuFormat
{
    s_menuAction firstItem;
    s_menuAction secondItem;
    s_menuAction thirdItem;
    s_menuAction fourthItem;
    s_menuAction fifthItem;
};

struct s_eventResult
{
    e_currentView view;
    e_resultType type;
    e_cities citySelection;
    s_menuAction menuAction;

};

#endif //DEFINE_H
