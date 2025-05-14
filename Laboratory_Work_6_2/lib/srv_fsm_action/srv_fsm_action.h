#ifndef SRV_FSM_ACTION_H
#define SRV_FSM_ACTION_H

#include "srv_global_vars.h"

void eastWestToGreen();
void eastWestToYellow();
void northSouthToGreen();
void northSouthToYellow();

void northSouthRedToYellow();
void eastWestRedToYellow();

void toNightModeBlinking();


#endif
