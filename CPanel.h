#ifndef _CPANEL_H
#define _CPANEL_H

#include <string>
#include <vector>

#include <SDL.h>

#include "CStats.h"

enum e_panelType
{
    e_stats = 0,
    e_string
};

class CPanel
{
    private:
        CStats displayStats;
        std::vector<std::string> displayStrings;
    public:
        static CPanel panelController;
        CPanel();
        void buildPanel(CStats displayStats);
        void buildPanel(std::vector<std::string> displayStrings);
        void onRender(SDL_Surface* dpy, int x, int y);
};

#endif //CPANEL_H
