#include "dd_joystick.h"
#include "srv_cond.h"
#include <Arduino.h>

Joystick::Joystick(int xPin, int yPin, int buttonPin)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->xValue = 0;
    this->yValue = 0;
    this->xBufferSP[JOYSTICK_SALT_AND_PIPER_FILTER_SIZE] = {0};
    this->yBufferSP[JOYSTICK_SALT_AND_PIPER_FILTER_SIZE] = {0};
    this->xBufferWA[JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE] = {0};
    this->yBufferWA[JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE] = {0};
    this->button = new Button(buttonPin);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

/**
 * Convert raw value to millivolt
 * 
 * @param rawValue raw value from the joystick (X, Y)
 * @param min minimum value
 * @param max maximum value
 * @return millivolt value
 */
int Joystick::convertToMilliVolt(int rawValue, int min = JOYSTICK_MILLIVOLT_MIN, int max = JOYSTICK_MILLIVOLT_MAX)
{
    // Way 1:
    // return JOYSTICK_MILLIVOLT_MAX * rawValue / JOYSTICK_RAW_VALUE_MAX;

    // // Way 2:
    return map(rawValue, JOYSTICK_RAW_VALUE_MIN, JOYSTICK_RAW_VALUE_MAX, min, max);
}

/**
 * Saturate the X-axis millivolt value
 * 
 * @param mVoltXValue millivolt value
 * @param min minimum value
 * @param max maximum value
 * @return saturated millivolt value
 */
int Joystick::saturate(int mVoltXValue, int min = JOYSTICK_MILLIVOLT_SAT_MIN, int max = JOYSTICK_MILLIVOLT_SAT_MAX)
{
    int mVoltXSatValue;
    if (mVoltXValue < min)
    {
        mVoltXSatValue = min;
    }
    else if (mVoltXValue > max)
    {
        mVoltXSatValue = max;
    } else
    {
        mVoltXSatValue = mVoltXValue;
    }
    
    return mVoltXSatValue;
}

/**
 * Salt and Piper filter
 * 
 * @param mVoltSatValue saturated millivolt value
 * @param filterSize filter size
 * @return filtered millivolt value
 */
int Joystick::saltAndPiperFilter(int mVoltSatValue, int *inputBuffer, int filterSize = JOYSTICK_SALT_AND_PIPER_FILTER_SIZE)
{
    int copyBuffer[filterSize];
    int medianValue;

    // Step 1: Push the value to the buffer
    fifoPush(mVoltSatValue, inputBuffer, filterSize);

    // Step 2: Copy the buffer
    bufferCopy(inputBuffer, copyBuffer, filterSize);

    // Step 3: Sort the buffer
    sort(copyBuffer, filterSize);

    // Step 4: Get the median value
    medianValue = copyBuffer[filterSize / 2];
    return medianValue;
}

/**
 * Weighted average filter
 * 
 * @param mVoltXSPFiltered filtered millivolt value
 * @param buffer buffer
 * @param bufferWeights buffer weights
 * @param filterSize filter size
 * @return filtered millivolt value
 */
int Joystick::weightedAverageFilter(int mVoltSPFiltered, int *inputBuffer, const int *bufferWeights = JOYSTICK_WEIGHTED_AVERAGE_FILTER_WEIGHTS, int filterSize = JOYSTICK_WEIGHTED_AVERAGE_FILTER_SIZE)
{
    long sum_up = 0;
    int sum_down = 0;
    int weightedAverageValue = 0;

    // Step 1: Push the value to the buffer
    fifoPush(mVoltSPFiltered, inputBuffer, filterSize);

    // Step 2: Weighted average
    for (int i = 0; i < filterSize; i++)
    {
        sum_up += (long)bufferWeights[i] * inputBuffer[i];
        sum_down += bufferWeights[i];
    }
    
    weightedAverageValue = sum_up / sum_down;
    return weightedAverageValue;
}

/**
 * Convert millivolt value to physical value
 * 
 * @param mVoltFilteredValue filtered millivolt value
 * @return physical value
 */
int Joystick::convertToPhysicalValue(int mVoltFilteredValue, int min = JOYSTICK_PHYSICAL_VALUE_MIN, int max = JOYSTICK_PHYSICAL_VALUE_MAX)
{
    return map(mVoltFilteredValue, JOYSTICK_MILLIVOLT_MIN, JOYSTICK_MILLIVOLT_MAX, min, max);
}

int Joystick::getX()
{
    int rawX = analogRead(xPin);
    int mVoltX = convertToMilliVolt(rawX);
    int mVoltXSaturated = saturate(mVoltX);
    int mVoltXSPFiltered = saltAndPiperFilter(mVoltXSaturated, this->xBufferSP);
    int mVoltXWAFFiltered = weightedAverageFilter(mVoltXSPFiltered, this->xBufferWA);
    int physicalX = convertToPhysicalValue(mVoltXWAFFiltered);
    this->xValue = physicalX;
     
    return this->xValue;
}

int Joystick::getY()
{
    int rawY = analogRead(yPin);
    int mVoltY = convertToMilliVolt(rawY, JOYSTICK_MILLIVOLT_MAX, JOYSTICK_MILLIVOLT_MIN);
    int mVoltYSaturated = saturate(mVoltY);
    int mVoltYSPFiltered = saltAndPiperFilter(mVoltYSaturated, this->yBufferSP);
    int mVoltYWAFFiltered = weightedAverageFilter(mVoltYSPFiltered, this->yBufferWA);
    int physicalY = convertToPhysicalValue(mVoltYWAFFiltered, JOYSTICK_PHYSICAL_VALUE_MAX, JOYSTICK_PHYSICAL_VALUE_MIN);
    this->yValue = physicalY;

    return this->yValue;
}

bool Joystick::getButtonState()
{
    return button->isPressed();
}
