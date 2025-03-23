#ifndef SRV_COND_H
#define SRV_COND_H

int fifoPush(int data, int *buffer, int bufferSize);
void bufferCopy(int *srcBuffer, int *dstBuffer, int bufferSize);
void sort(int *buffer, int bufferSize);

#endif