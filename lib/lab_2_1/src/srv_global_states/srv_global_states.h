#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

struct GlobalVariables {
    bool led1State; // Task 1 provides
    bool led2State; // Task 2 provides
    int counter; // Task 3 provides
};

extern volatile GlobalVariables globalStates;

void globalStatesSetup();
void setLed1State(bool state);
void setLed2State(bool state);
void incrementCounter();
void decrementCounter();
void setCounter(int value);
bool getLed1State();
bool getLed2State();
int getCounter();

#endif