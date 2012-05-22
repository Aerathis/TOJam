#include "CStats.h"

CStats::CStats()
{
    cash = 0;
    gas = 0;
}

void CStats::spendCash(int amount)
{
    cash -= amount;
}

void CStats::gainCash(int amount)
{
    cash += amount;
}

void CStats::getGas(int amount)
{
    gas += amount;
}
