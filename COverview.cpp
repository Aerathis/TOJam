#include "COverview.h"

std::vector<CCity*> COverview::cityList;

COverview::COverview()
{
    cityList.clear();
    height = width = 0;
    overviewMap = NULL;
}

bool COverview::onLoad(char* file)
{
    cityList.clear();

    FILE* fileHandle = fopen(file, "r");

    if (fileHandle == NULL)
    {
        return false;
    }

    char overviewSurface[80];
    fscanf(fileHandle, "%s\n",overviewSurface);
    overviewMap = CSurface::onLoad(overviewSurface);
    int numCities;
    fscanf(fileHandle,"%d\n",&numCities);
    for(int i = 0; i < numCities; i++)
    {
        char cityFileName[80];
        fscanf(fileHandle,"%s\n",cityFileName);
        CCity* tempCity = new CCity();
        tempCity->onLoad(cityFileName);
        cityList.push_back(tempCity);
    }
    fclose(fileHandle);
    return true;
}

void COverview::onRender(SDL_Surface* dpy)
{
    if (dpy == NULL || overviewMap == NULL)
        return;
    CSurface::onDraw(dpy, overviewMap, 0, 0);
}


void COverview::onCleanup()
{
    if (overviewMap)
    {
        SDL_FreeSurface(overviewMap);
    }
    overviewMap = NULL;
}

e_cities COverview::handleClick(int xPos, int yPos)
{
    //Return the numeric index of the city that was clicked on

    for (int i = 0; i < cityList.size(); i++)
    {
        CCity tempCity = *cityList[i];
        int cityx, cityy;
        cityx = tempCity.getMapX();
        cityy = tempCity.getMapY();
        if (xPos > cityx - 25 && xPos < cityx + 25 &&
            yPos > cityy - 25 && yPos < cityy + 25)
            {
                return tempCity.getNameEnum();
            }
    }
    return e_none;
}

void COverview::handleMouseOver(int xPos, int yPos)
{
    // Draw popup or panel or whatever when mouse over a city
}
