#include "COverview.h"

COverview::COverview()
{
    cityList.clear();
    height = width = 0;
    overviewMap = NULL;
}

bool COverview::onLoad(char* file)
{
    cityList.clear();

    FILE* fileHandle = fopen("./cities", "r");

    if (fileHandle == NULL)
    {
        return false;
    }
    int numCities;
    fscanf(fileHandle,"%d\n",&numCities);
    for(int i = 0; i < numCities; i++)
    {
        char cityName[80];
        char cityFileName[80];
        fscanf(fileHandle,"%s,%s\n",cityName,cityFileName);
        CCity tempCity;
        tempCity.onLoad(cityFileName);
        cityList.push_back(&tempCity);
    }

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

int COverview::handleClick(int xPos, int yPos)
{
    //Return the numeric index of the city that was clicked on
    return -1;
}
