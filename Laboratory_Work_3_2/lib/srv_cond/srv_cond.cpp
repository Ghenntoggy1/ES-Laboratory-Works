#include "srv_cond.h"
#include <Arduino.h>

int fifoPush(int data, int *buffer, int bufferSize)
{
    for (int i = bufferSize - 1; i >= 0; i--)
    {
        buffer[i] = buffer[i - 1];
    }

    buffer[0] = data;
    return data;
}

void bufferCopy(int *srcBuffer, int *dstBuffer, int bufferSize)
{
    for (int i = 0; i < bufferSize; i++)
    {
        dstBuffer[i] = srcBuffer[i];
    }

}

int compare( const void *a, const void *b)
{
    float *int_a = (float *) a;
    float *int_b = (float *) b;

    if (*int_a > *int_b) 
    {
        return 1;
    }
    else if (*int_a < *int_b) 
    {
        return -1;
    }

    return 0;
}


void sort(int *buffer, int bufferSize)
{
    qsort(buffer, bufferSize, sizeof(int), compare);
}