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
    fscanf(fileHandle,"%[^\n]",name);
    cityName = name;
    if (cityName == "Oil Springs")
    {
        nameEnum = e_first;
    }
    else if (cityName == "Beaver Dam")
    {
        nameEnum = e_second;
    }
    else if (cityName == "Deadman's Bay")
    {
        nameEnum = e_third;
    }
    else if (cityName == "Wild Goose")
    {
        nameEnum = e_fourth;
    }
    else if (cityName == "St-Louis-du-Ha! Ha!")
    {
        nameEnum = e_fifth;
    }
    else if (cityName == "Bacon Ridge")
    {
        nameEnum = e_home;
    }
    char citySurface[80];
    fscanf(fileHandle, "%s\n",citySurface);
    cityView = CSurface::onLoad(citySurface);

    int xmap, ymap;
    fscanf(fileHandle,"%d,%d\n",&xmap,&ymap);
    mapX = xmap;
    mapY = ymap;

    int numCitizens;
    fscanf(fileHandle,"%d\n",&numCitizens);
    for (int i = 0; i < numCitizens; i++)
    {
        char citFile[80];
        fscanf(fileHandle, "%s\n",citFile);
        CCitizen* tempCit = new CCitizen();
        tempCit->onLoad(citFile);
        citizens.push_back(tempCit);
    }

    fclose(fileHandle);
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

int CCity::getNameEnum()
{
    return nameEnum;
}

int CCity::getMapX()
{
    return mapX;
}

int CCity::getMapY()
{
    return mapY;
}

std::string CCity::getCityName()
{
    return cityName;
}

std::vector<CCitizen*> CCity::getCitizenList()
{
    return citizens;
}
