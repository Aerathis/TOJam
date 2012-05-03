#ifndef _CAPP_H
#define _CAPP_H

#include <SDL/SDL.h>

class CApp
{
  private:
    bool running;

    SDL_Surface* dpy;

  public:
    CApp();

    int onExecute();
    bool onInit();
    void onEvent(SDL_Event* Event);
    void onLoop();
    void onRender();
    void onCleanup();
};

#endif //CAPP_H
