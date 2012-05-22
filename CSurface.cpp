#include "CSurface.h"

CSurface::CSurface()
{

}

SDL_Surface* CSurface::onLoad(char* file)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if ((Surf_Temp = SDL_LoadBMP(file)) == NULL)
    {
        return NULL;
    }

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool CSurface::onDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
    if (dest == NULL || src == NULL)
    {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;

    SDL_BlitSurface(src, NULL, dest, &DestR);

    return true;
}

bool CSurface::onDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h)
{
    if (dest == NULL || src == NULL)
    {
        return false;
    }

    SDL_Rect destR;

    destR.x = x;
    destR.y = y;

    SDL_Rect srcR;
    srcR.x = x2;
    srcR.y = y2;
    srcR.w = w;
    srcR.h = h;

    SDL_BlitSurface(src, &srcR, dest, &destR);

    return true;
}

bool CSurface::transparent(SDL_Surface* dest, int r, int g, int b)
{
    if (dest == NULL)
    {
        return false;
    }

    SDL_SetColorKey(dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(dest->format,r,g,b));

    return true;
}
