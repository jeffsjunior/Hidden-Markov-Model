#ifndef TRUERANDOM_H
#define TRUERANDOM_H
#include <Arduino.h>

//Code obtained in https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94

#define ANALOGPIN  A0

const int waitTime = 16;


byte getTrueRotateRandomByte();
long trueRandom(long howsmall, long howbig);
#endif