#include "CPanel.h"

CPanel CPanel::panelController;

CPanel::CPanel()
{
    displayStrings.clear();
}

void CPanel::buildPanel(CStats inStats)
{
    displayStats = inStats;
}

void CPanel::buildPanel(std::vector<std::string> inStrings)
{
    displayStrings = inStrings;
}

void CPanel::onRender(SDL_Surface* dpy, int x, int y)
{

}
