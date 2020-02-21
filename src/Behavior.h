#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include <Arduino.h>


class Behavior{

    private:
        Stream *_streamRef;

    public:
        Behavior();

        void setSerial(Stream *streamObject);
        void smile(void);
        void kiss(void);
        void cry(void);
        void moan(void);
        void yell(void);
};

#endif