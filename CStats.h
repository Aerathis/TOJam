#ifndef _CSTATS_H
#define _CSTATS_H

#include <vector>

class CStats
{
    private:
        int cash;
        int gas;

    public:
        CStats();

        int getCash();
        void spendCash(int amount);
        void gainCash(int amount);
        void getGas(int amount);
};

#endif //CSTATS_H
