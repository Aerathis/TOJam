#include "CApp.h"

e_currentView CApp::viewControl;

CApp::CApp()
{
    dpy = NULL;
    running = true;
    currentView = e_other;
    prevView = e_other;
    time = 0;
    CEntity::entityList.push_back(&dude);
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
    if (!dude.onLoad("./car.bmp",0,0,0))
    {
        return false;
    }
    if (!gameWorld.onLoad("./cities"))
    {
        return false;
    }
    if (!CInventory::inventoryControl.onLoad())
    {
        return false;
    }
    if (!CItem::onLoad("./items"))
    {
        return false;
    }
    if (!CNumbers::onLoad())
    {
        return false;
    }
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    currentView = e_overView;
    prevView = e_overView;

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
        if (currentView == e_overView)
            CEntity::entityList[i]->onLoop(&currentView);
    }
    if (currentView != prevView)
    {
        switch (currentView)
        {
            case e_city:
            {
                CMenu::menuController.clearMenus();
            }
            break;
        }
    }
    prevView = currentView;
}

void CApp::onRender()
{
    switch (currentView)
    {
        case e_overView:
            {
                // Render just the overview map
                gameWorld.onRender(dpy);
                CInventory::inventoryControl.onRender(dpy);
                CEntity::entityList[0]->onRender(dpy);
            }
            break;
        case e_city:
            {
                // Render the city map with a manu of the citizens overlaying it
                CEntity::entityList[0]->getCurrentLocation()->onRender(dpy);
                CInventory::inventoryControl.onRender(dpy);
                CCity* location = CEntity::entityList[0]->getCurrentLocation();
                int numCits = location->getCitizenList().size();
                for (int i = 0; i < numCits; i++)
                {
                    CEntity::entityList[0]->getCurrentLocation()->getCitizenList()[i]->onRender(dpy, (200 * i) + 50, 300);
                }
            }
            break;
        case e_convo:
            {
                // Render the current conversation and a menu of choices overlaying it
                CEntity::entityList[0]->getCurrentConvo()->onRender(dpy,0,0);
                CInventory::inventoryControl.onRender(dpy);
                CMenu::menuController.buildMenu(CEntity::entityList[0]->getCurrentConvo());
                CMenu::menuController.onRender(dpy, 0, 0);
            }
            break;
        default: {}
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
    s_eventResult results;
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
                results.menuAction = CMenu::menuController.handleClick(x, y);
                switch (results.menuAction.selection)
                {
                    case e_menuLeave:
                        {
                            results.type = e_leave;
                            results.view = e_convo;
                        }
                        break;
                }
                CEntity::entityList[0]->processEventResults(results, &currentView);
            }
        }
        else
        {

        }
    }
    else if (currentView == e_city)
    {
        s_eventResult results;
        int selection;
        selection = CEntity::entityList[0]->getCurrentLocation()->handleClick(x,y);
        if (selection != -1)
        {
            results.type = e_enterConvo;
            results.convoChoice = selection;
            results.view = e_city;
            CEntity::entityList[0]->processEventResults(results, &currentView);
        }
        else if (selection == -1)
        {
            results.type = e_leave;
            results.view = e_city;
            CEntity::entityList[0]->processEventResults(results,&currentView);
        }
    }
    else if (currentView == e_overView)
    {
        results.citySelection = gameWorld.handleClick(x, y);
        if (results.citySelection != e_none)
        {
            results.type = e_moveToCity;
            results.view = e_overView;
            CEntity::entityList[0]->processEventResults(results,&currentView);
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
        if (CMenu::menuController.isBuilt())
        {
            if (!CMenu::menuController.isActive())
            {
                CMenu::menuController.makeActive();
            }
            else
            {
                CMenu::menuController.handleMove(x,y);
            }
        }
        else
        {

        }
  }
  if (currentView == e_overView)
  {
        gameWorld.handleMouseOver(x, y);
  }
}

int main(int argc, char** argv)
{
    CApp theApp;
    return theApp.onExecute();
}
