#include "Behavior.h"

Behavior::Behavior(){
}

void Behavior::setSerial(Stream *streamObject){
    _streamRef=streamObject;
}

void Behavior::smile(void){
    _streamRef->println("Smile");
}

void Behavior::kiss(void){
    _streamRef->println("Kiss");
}

void Behavior::cry(void){
    _streamRef->println("Cry");
}

void Behavior::moan(void){
    _streamRef->println("Moan");
}

void Behavior::yell(void){
    _streamRef->println("Yell");
}
