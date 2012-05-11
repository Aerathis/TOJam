#ifndef _CAPP_H
#define _CAPP_H

#include <SDL.h>

#include "CAnimation.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEvent.h"
#include "CMenu.h"
#include "COverview.h"
#include "CPanel.h"
#include "CSurface.h"
#include "Define.h"

class CApp : public CEvent
{
  private:
    bool running;

    SDL_Surface* dpy;

    CEntity dude;
    COverview gameWorld;
    e_currentView currentView;
    int time;

  public:
    CApp();

    int onExecute();
    bool onInit();
    void onEvent(SDL_Event* Event);
    void onLoop();
    void onRender();
    void onCleanup();

    void onExit();
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void onLButtonDown(int x, int y);
    void onMouseMove(int x, int y, int xrel, int yrel, bool lDown, bool rDown, bool mDown);
};

#endif //CAPP_H
