#include "CApp.h"

#include <iostream>
e_currentView CApp::viewControl;

CApp::CApp()
{
    dpy = NULL;
    running = true;
    currentView = e_other;
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
        CEntity::entityList[i]->onLoop(&currentView);
    }
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
                CMenu::menuController.onRender(dpy, 0, 0);
            }
            break;
        case e_convo:
            {
                // Render the current conversation and a menu of choices overlaying it
                CEntity::entityList[0]->getCurrentConvo()->onRender(dpy,0,0);
                CInventory::inventoryControl.onRender(dpy);
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
                CMenu::menuController.handleClick(x, y);
            }
        }
        else
        {

        }
    }
    if (currentView == e_city)
    {
        s_eventResult results;
        int selection;
        if (CMenu::menuController.isBuilt())
        {
            if (!CMenu::menuController.isActive())
            {
                CMenu::menuController.makeActive();
            }
            else
            {
                selection = CMenu::menuController.handleClick(x,y);
                if (selection != -1)
                {
                    switch (selection)
                    {
                        case 0: results.menuAction = CMenu::menuController.getMenuFormat().firstItem;
                        case 1: results.menuAction = CMenu::menuController.getMenuFormat().secondItem;
                        case 3: results.menuAction = CMenu::menuController.getMenuFormat().thirdItem;
                        case 4: results.menuAction = CMenu::menuController.getMenuFormat().fourthItem;
                        case 5: results.menuAction = CMenu::menuController.getMenuFormat().fifthItem;
                    }

                    if (results.menuAction.selection == e_menuBuy)
                    {
                        results.type = e_buy;
                    }
                    else if (results.menuAction.selection == e_menuSell)
                    {
                        results.type = e_sell;
                    }
                    else if (results.menuAction.selection == e_startConvo)
                    {
                        results.type = e_enterConvo;
                    }
                    else
                    {
                        results.type = e_leave;
                    }
                }
            }
        }
        else{}
    }
    if (currentView == e_overView)
    {
        int selection = gameWorld.handleClick(x, y);
        if (selection != -1)
        {
            results.type = e_moveToCity;
            results.view = e_overView;
            switch (selection)
            {
                case 0: results.citySelection = e_first; break;
                case 1: results.citySelection = e_second; break;
                case 2: results.citySelection = e_third; break;
                case 3: results.citySelection = e_fourth; break;
                case 4: results.citySelection = e_fifth; break;
                case 5: results.citySelection = e_home; break;
                default: {}
            }
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
