#ifndef _CENTITY_H
#define _CENTITY_H

#include <vector>

#include "CArea.h"
#include "CAnimation.h"
#include "CCity.h"
#include "CCitizen.h"
#include "CFPS.h"
#include "CInventory.h"
#include "CStats.h"
#include "CSurface.h"
#include "Define.h"

class CEntity
{
    public :
        static std::vector<CEntity*> entityList;

    protected:
        SDL_Surface* entSurface;
        CAnimation animController;
        CCity* location;
        CCitizen* currentConvo;


    public:

        float x;
        float y;
        int width;
        int height;


        CEntity();
        virtual ~CEntity();

        void onMove(float moveX, float moveY);
        void stopMove();
        virtual bool onLoad(char* file, int width, int height, int maxFrames);
        virtual void onLoop();
        virtual void onRender(SDL_Surface* dpy);
        virtual void onCleanup();

        CStats* getStatsPtr();

        void buyFromCitizen(s_saleItem item, int amount);
        void sellToCitizen(s_saleItem item);

        void processEventResults(s_eventResult results);

        //virtual void onAnimate();
        //virtual void onCollision(CEntity* entity);

    private:
        bool posValid(int newX, int newY);
        bool posValidTile(CTile* tile);
        bool posValidEntity(CEntity* entity, int newX, int newY);
        CStats playerStats;
};
#endif //CENTITY_H
