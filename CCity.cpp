#include "CCity.h"

CCity::CCity()
{
    citizens.clear();
    cityView = NULL;
    neighbours.clear();
    cityName = "";
}

bool CCity::onLoad(char* file)
{
    citizens.clear();
    FILE* fileHandle = fopen(file,"r");
    if (fileHandle == NULL)
        return false;
    char name[80];
    fscanf(fileHandle,"%s\n",name);
    cityName = name;
    int numCitizens;
    fscanf(fileHandle,"%d\n",&numCitizens);
    for (int i = 0; i < numCitizens; i++)
    {
        char citFile[80];
        fscanf(fileHandle, "%s\n",citFile);
        CCitizen tempCit;
        tempCit.onLoad(citFile);
        citizens.push_back(&tempCit);
    }
    return true;
}

void CCity::onRender(SDL_Surface* dpy)
{
    if (dpy == NULL || cityView == NULL)
        return;
    CSurface::onDraw(dpy, cityView, 0, 0);
}

void CCity::onCleanup()
{
    if (cityView)
    {
        SDL_FreeSurface(cityView);
    }
    cityView = NULL;
}
