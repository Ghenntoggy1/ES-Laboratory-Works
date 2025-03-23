#include "dd_potentiometer.h"
#include "srv_cond.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    this->potValue = 0;

    this->rawPotValue = 0;
    this->potMilliVolt = 0;
    this->potSatMilliVolt = 0;
    this->potSaltPiperFilteredMilliVolt = 0;
    this->potWeightedAverageFilteredMilliVolt = 0;
    this->potPhysical = 0;

    this->bufferSP[POTENTIOMETER_SALT_AND_PIPER_FILTER_SIZE] = {0};
    this->bufferWA[POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_SIZE] = {0};

    pinMode(pin, INPUT);
}

int Potentiometer::convertToMilliVolt(int rawValue, int min = POTENTIOMETER_MILLIVOLT_MIN, int max = POTENTIOMETER_MILLIVOLT_MAX) {
    // Way 1:
    // return POTENTIOMETER_MILLIVOLT_MAX * rawValue / POTENTIOMETER_RAW_VALUE_MAX;

    // // Way 2:
    return map(rawValue, POTENTIOMETER_RAW_VALUE_MIN, POTENTIOMETER_RAW_VALUE_MAX, min, max);
}

int Potentiometer::saturate(int mVoltValue, int min = POTENTIOMETER_MILLIVOLT_SAT_MIN, int max = POTENTIOMETER_MILLIVOLT_SAT_MAX) {
    int mVoltPotSatValue;
    if (mVoltValue < min) {
        mVoltPotSatValue = min;
    } else if (mVoltValue > max) {
        mVoltPotSatValue = max;
    } else {
        mVoltPotSatValue = mVoltValue;
    }

    return mVoltPotSatValue;
}

int Potentiometer::saltAndPiperFilter(int mVoltSatValue, int *inputBuffer, int filterSize) {
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

int Potentiometer::weightedAverageFilter(int mVoltSPFiltered, int *inputBuffer, const int *bufferWeights, int filterSize) {
    long sum_up = 0;
    int sum_down = 0;
    int weightedAverageValue = 0;

    // Step 1: Push the value to the buffer
    fifoPush(mVoltSPFiltered, inputBuffer, filterSize);

    // Step 2: Weighted average
    for (int i = 0; i < filterSize; i++) {
        sum_up += (long)bufferWeights[i] * inputBuffer[i];
        sum_down += bufferWeights[i];
    }

    weightedAverageValue = sum_up / sum_down;
    return weightedAverageValue;
}

int Potentiometer::convertToPhysicalValue(int mVoltFilteredValue, int min = POTENTIOMETER_PHYSICAL_VALUE_MIN, int max = POTENTIOMETER_PHYSICAL_VALUE_MAX) {
    return map(mVoltFilteredValue, POTENTIOMETER_MILLIVOLT_MIN, POTENTIOMETER_MILLIVOLT_MAX, min, max);
}

int Potentiometer::getPotValue() {
    potValue = analogRead(pin);

    this->rawPotValue = potValue;

    this->potMilliVolt = convertToMilliVolt(rawPotValue);

    this->potSatMilliVolt = saturate(potMilliVolt);

    this->potSaltPiperFilteredMilliVolt = saltAndPiperFilter(potSatMilliVolt, this->bufferSP, POTENTIOMETER_SALT_AND_PIPER_FILTER_SIZE);

    this->potWeightedAverageFilteredMilliVolt = weightedAverageFilter(potSaltPiperFilteredMilliVolt, this->bufferWA, POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_WEIGHTS, POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_SIZE);

    this->potPhysical = convertToPhysicalValue(potWeightedAverageFilteredMilliVolt);

    return potValue;
}

int Potentiometer::getRawPotValue() {
    return rawPotValue;
}

int Potentiometer::getPotMilliVolt() {
    return potMilliVolt;
}

int Potentiometer::getPotSatMilliVolt() {
    return potSatMilliVolt;
}

int Potentiometer::getPotSaltPiperFilteredMilliVolt() {
    return potSaltPiperFilteredMilliVolt;
}

int Potentiometer::getPotWeightedAverageFilteredMilliVolt() {
    return potWeightedAverageFilteredMilliVolt;
}

int Potentiometer::getPotPhysical() {
    return potPhysical;
}