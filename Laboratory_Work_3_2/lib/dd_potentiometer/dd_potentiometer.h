#ifndef DD_POTENTIOMETER_H
#define DD_POTENTIOMETER_H

#define POTENTIOMETER_RAW_VALUE_MIN 0
#define POTENTIOMETER_RAW_VALUE_MAX 1023
#define POTENTIOMETER_MILLIVOLT_MIN 0
#define POTENTIOMETER_MILLIVOLT_MAX 5000
#define POTENTIOMETER_MILLIVOLT_SAT_MIN 1000
#define POTENTIOMETER_MILLIVOLT_SAT_MAX 4000
#define POTENTIOMETER_SALT_AND_PIPER_FILTER_SIZE 5
#define POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_SIZE 4
static const int POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_WEIGHTS[POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_SIZE] = {50, 25, 15, 10};
#define POTENTIOMETER_PHYSICAL_VALUE_MIN 0
#define POTENTIOMETER_PHYSICAL_VALUE_MAX 10000

class Potentiometer {
    private:
        int pin;
        int potValue;

        int rawPotValue;
        int potMilliVolt;
        int potSatMilliVolt;
        int potSaltPiperFilteredMilliVolt;
        int potWeightedAverageFilteredMilliVolt;
        int potPhysical;

        int bufferSP[POTENTIOMETER_SALT_AND_PIPER_FILTER_SIZE];
        int bufferWA[POTENTIOMETER_WEIGHTED_AVERAGE_FILTER_SIZE];
        int convertToMilliVolt(int rawValue, int min, int max);
        int saturate(int mVoltValue, int min, int max);
        int saltAndPiperFilter(int mVoltSatValue, int *inputBuffer, int filterSize);
        int weightedAverageFilter(int mVoltSPFiltered, int *inputBuffer, const int *bufferWeights, int filterSize);
        int convertToPhysicalValue(int mVoltFilteredValue, int min, int max);
    
    public:
        Potentiometer(int pin);
        int getPotValue();
        int getRawPotValue();
        int getPotMilliVolt();
        int getPotSatMilliVolt();
        int getPotSaltPiperFilteredMilliVolt();
        int getPotWeightedAverageFilteredMilliVolt();
        int getPotPhysical();
};

#endif