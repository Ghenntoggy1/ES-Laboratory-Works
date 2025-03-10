#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

struct GlobalVariables_lab_2_1 {
    bool led1State; // Task 1 provides
    bool led2State; // Task 2 provides
    int counter; // Task 3 provides
};

extern volatile GlobalVariables_lab_2_1 globalStates;

void lab_2_1_globalStatesSetup();
void lab_2_1_setLed1State(bool state);
void lab_2_1_setLed2State(bool state);
void lab_2_1_setCounter(int value);
bool lab_2_1_getLed1State();
bool lab_2_1_getLed2State();
int lab_2_1_getCounter();

#endif