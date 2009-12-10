/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 */

 
#pragma once
#include "Common.h"

inline DWORD GetMSTime() {return GetTickCount();}

inline DWORD GetMSTimeDiff(DWORD oldMSTime, DWORD newMSTime)
{
    // GetMSTime() have limited data range and this is case when it overflow in this tick
    if(oldMSTime > newMSTime)
        return (0xFFFFFFFF - oldMSTime) + newMSTime;
    else
        return newMSTime - oldMSTime;
}
