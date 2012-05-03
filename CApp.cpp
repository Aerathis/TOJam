#include "CApp.h"

CApp::CApp()
{
    dpy = NULL;
    running = true;
}

bool CApp::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }
    if ((dpy = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }
    return true;
}

void CApp::onEvent(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        running = false;
    }
}

void CApp::onLoop()
{

}

void CApp::onRender()
{

}

void CApp::onCleanup()
{
    SDL_Quit();
}

int CApp::onExecute()
{
    if (!onInit())
    {
        return 1;
    }

    SDL_Event event;

    while (running)
    {
        while(SDL_PollEvent(&event))
        {
            onEvent(&event);
        }

        onLoop();
        onRender();
    }
    onCleanup();
    return 0;
}

int main(int argc, char** argv)
{
    CApp theApp;
    return theApp.onExecute();
}
