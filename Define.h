#ifndef _DEFINE_H
#define _DEFINE_H

#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define TILE_SIZE 16
#define WWIDTH 800
#define WHEIGHT 600
#define PORTRAITWIDTH 100
#define MENUITEMWIDTH 50

#include <string>

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

struct s_inventoryItem
{
    std::string name;
    int value;
    int quantity;
};

struct s_item
{
    std::string name;
    int value;
};

struct s_menuFormat
{
    int firstItem;
    int secondItem;
    int thirdItem;
    int fourthItem;
    int fifthItem;
};

struct s_eventResult
{
    e_currentView view;
    e_resultType type;
    int selection;
};

#endif //DEFINE_H
