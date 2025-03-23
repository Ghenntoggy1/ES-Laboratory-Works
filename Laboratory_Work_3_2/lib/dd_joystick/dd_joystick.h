#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "dd_button.h"

#define JOYSTICK_RAW_VALUE_MIN 0
#define JOYSTICK_RAW_VALUE_MAX 1023
#define JOYSTICK_MILLIVOLT_MIN 0
#define JOYSTICK_MILLIVOLT_MAX 5000
#define JOYSTICK_MILLIVOLT_SAT_MIN 1000
#define JOYSTICK_MILLIVOLT_SAT_MAX 4000
#define JOYSTICK_SALT_AND_PIPER_FILTER_SIZE 5
#define JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE 4
static const int JOYSTICK_WEIGHTED_AVERAGE_FILTER_WEIGHTS[JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE] = {50, 25, 15, 10};
#define JOYSTICK_PHYSICAL_VALUE_MIN -100
#define JOYSTICK_PHYSICAL_VALUE_MAX 100

class Joystick {
    private:
        int xPin;
        int yPin;
        int xValue;
        int yValue;
        int xBufferSP[JOYSTICK_SALT_AND_PIPER_FILTER_SIZE];
        int yBufferSP[JOYSTICK_SALT_AND_PIPER_FILTER_SIZE];
        int xBufferWA[JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE];
        int yBufferWA[JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE];
        Button *button;
        int convertToMilliVolt(int rawValue, int min, int max);
        int saturate(int mVoltXValue, int min, int max);
        int saltAndPiperFilter(int mVoltSatValue, int *inputBuffer, int *copyBuffer, int filterSize);
        int weightedAverageFilter(int mVoltXSPFiltered, const int *bufferWeights, int filterSize);
        int convertToPhysicalValue(int mVoltFilteredValue, int min, int max);
    
    public:
        Joystick(int xPin, int yPin, int buttonPin);
        int getX();
        int getY();
        int getMilliVoltX();
        int getMilliVoltY();
        int getSatMilliVoltX();
        int getSatMilliVoltY();
        int getSaltPiperFilteredMilliVoltX();
        int getSaltPiperFilteredMilliVoltY();
        int getWeightedAverageFilteredMilliVoltX();
        int getWeightedAverageFilteredMilliVoltY();
        int getPhysicalX();
        int getPhysicalY();
        bool getButtonState();
};

#endif