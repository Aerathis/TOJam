#include "CApp.h"

CApp::CApp()
{
    dpy = NULL;
    running = true;
    currentView = e_other;
    time = 0;
}

bool CApp::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }
    if ((dpy = SDL_SetVideoMode(WWIDTH,WHEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }
    if (!gameWorld.onLoad("./world.world"))
    {
        return false;
    }
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    currentView = e_overView;

    return true;
}

void CApp::onEvent(SDL_Event* Event)
{
    CEvent::onEvent(Event);
}

void CApp::onLoop()
{
    for (int i = 0; i < CEntity::entityList.size(); i++)
    {
        if (!CEntity::entityList[i])
            continue;
        CEntity::entityList[i]->onLoop();
    }
}

void CApp::onRender()
{
    for (int i = 0; i < CEntity::entityList.size(); i++)
    {
        if (!CEntity::entityList[i])
            continue;
        CEntity::entityList[i]->onRender(dpy);
    }
    SDL_Flip(dpy);
}

void CApp::onCleanup()
{
    SDL_FreeSurface(dpy);
    for (int i = 0; i < CEntity::entityList.size(); i++)
    {
        if (!CEntity::entityList[i])
            continue;

        CEntity::entityList[i]->onCleanup();
    }

    CEntity::entityList.clear();
    SDL_Quit();
}

void CApp::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
        case SDLK_ESCAPE: running = false; break;
        default:{}
    }
}

void CApp::onExit()
{
    running = false;
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

void CApp::onLButtonDown(int x, int y)
{
    if (currentView == e_convo)
    {
        if (CMenu::menuController.isBuilt())
        {
            if (!CMenu::menuController.isActive())
            {
                CMenu::menuController.makeActive();
            }
            else
            {
                CMenu::menuController.handleClick(x, y);
            }
        }
    }
    if (currentView == e_city)
    {

    }
    if (currentView == e_overView)
    {
        int selection = gameWorld.handleClick(x, y);
        if (selection != -1)
        {
            s_eventResult results;
            results.type = e_moveToCity;
            results.view = e_overView;
            results.selection = selection;
            CEntity* tempDude = CEntity::entityList[0];
            tempDude->processEventResults(results);
        }
    }
}

void CApp::onMouseMove(int x, int y, int xrel, int yrel, bool lDown, bool rDown, bool mDown)
{
  if (currentView == e_convo)
  {
      if (CMenu::menuController.isBuilt())
      {
          if (!CMenu::menuController.isActive())
          {
              CMenu::menuController.makeActive();
          }
          else
          {
              CMenu::menuController.handleMove(x, y);
          }
      }
      else
      {

      }
  }
  if (currentView == e_city)
  {

  }
  if (currentView == e_overView)
  {

  }
}

int main(int argc, char** argv)
{
    CApp theApp;
    return theApp.onExecute();
}
