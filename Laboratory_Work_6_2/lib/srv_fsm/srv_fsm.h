#ifndef SRV_FSM_H
#define SRV_FSM_H

#include <Arduino.h>
#include "srv_global_vars.h"
#include "srv_fsm_action.h"

typedef struct {
    void (*onEntryAction)();
    unsigned long time;
    int next[4];
} FSMState;


extern const FSMState FSMStatesStruct[];


#endif
