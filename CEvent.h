#ifndef _CEVENT_H
#define _CEVENT_H

#include <SDL.h>

class CEvent
{
    public:
    CEvent();
    virtual ~CEvent();

    virtual void onEvent(SDL_Event* Event);
    virtual void onInputFocus();
    virtual void onInputBlur();
    virtual void onKeyDown(SDLKey key, SDLMod mod, Uint16 unicode);
    virtual void onKeyUp(SDLKey key, SDLMod mod, Uint16 unicode);
    virtual void onMouseFocus();
    virtual void onMouseBlur();
    virtual void onMouseMove(Uint16, Uint16, Sint16, Sint16, bool, bool, bool);
    virtual void onMouseWheel(bool,bool);
    virtual void onLButtonDown(int,int);
    virtual void onLButtonUp(int,int);
    virtual void onRButtonDown(int,int);
    virtual void onRButtonUp(int,int);
    virtual void onMButtonDown(int,int);
    virtual void onMButtonUp(int,int);
    virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
    virtual void onJoyButtonDown(Uint8 which, Uint8 button);
    virtual void onJoyButtonUp(Uint8 which, Uint8 button);
    virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);
    virtual void onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
    virtual void onMinimize();
    virtual void onRestore();
    virtual void onResize(int, int);
    virtual void onExpose();
    virtual void onExit();
    virtual void onUser(Uint8 type, int code, void* data1, void* data2);
};

#endif //CEVENT_H
