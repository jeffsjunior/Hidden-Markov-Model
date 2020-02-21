#include "HMM.h"
#include "TrueRandom.h"

//Definitions
const char* const statesStr[nStates] = {"Happy", "Sad", "Angry"};
const char* const behaviorsStr[nBehaviors] = {"Smile", "Kiss", "Cry", "Moan", "Yell"};

//Transition and Emission Parameters of the Hidden Markov Model
//                       state      Transition              Emission
sState statesArray[] = {{sHappy, {0.8, 0.1, 0.1}, {0.4, 0.4, 0.068, 0.066, 0.066}},
                        {sSad,   {0.1, 0.8, 0.1}, {0.05, 0.05, 0.4, 0.4, 0.1}},
                        {sAngry, {0.1, 0.1, 0.8}, {0.05, 0.05, 0.1, 0.2, 0.6}}};

sBehavior behaviorsArray[] = {{smile, &Behavior::smile},
                              {kiss, &Behavior::kiss},
                              {cry, &Behavior::cry},
                              {moan, &Behavior::moan},
                              {yell, &Behavior::yell}};

//Functions
sState nextState(sState currentState){
    uint8_t i = sortPMF(currentState.transitionProb, nStates);
    return statesArray[i];
}

uint8_t sortPMF(float pdf[], uint8_t numel){
    float x = trueRandom(0, 1025)/1024.0;
    float pCum = pdf[0];

    uint8_t i = 0;
    while((x > pCum) && (i < numel)){
        i++;
        pCum += pdf[i];
    }
    return i;
}

tBehavior runBehavior(sState currentState, Behavior behaviorObj){
    uint8_t i = sortPMF(currentState.behaviorProb, nBehaviors);
    (behaviorObj.*behaviorsArray[i].run)();

    return behaviorsArray[i].behavior;
}


//// Utils
void printData(sState sCurrent){
    Serial.println("~~~~~~~~~~~~~~~~~");
    Serial.println();
    Serial.println("~~~~~~~~~~~~~~~~~");
    Serial.print("~~~Current State~~~ "); Serial.println(statesStr[sCurrent.state]);
    Serial.println("~~Next State Prob.~~ "); 
    for(int i = 0; i<nStates;i++)
    {
        Serial.print(statesStr[i]);Serial.print(": ");
        Serial.println(statesArray[sCurrent.state].transitionProb[i]);
    }
    Serial.println();

    Serial.println("~~Behavior Prob.~~ "); 
    for(int i = 0; i<nBehaviors;i++)
    {
        Serial.print(behaviorsStr[i]);Serial.print(": ");
        Serial.println(statesArray[sCurrent.state].behaviorProb[i]);
    }
    Serial.println();
    Serial.println("~~Chosen Behavior~~");
}