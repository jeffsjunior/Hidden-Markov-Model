/*  This code implements a Hidden Markov Model and verifies
    the selected probabilities.

    The states, behaviors, and proabilites are to be placed
    in the HMM.h/.cpp files.

    A template class for the behaviors are in the Behavior.h
    file.

    Implemented by: Jefferson Junior.
    Date: February 21, 2020.
*/


#include <Arduino.h>
#include "Behavior.h"
#include "HMM.h"

long HMMTableTests[nStates][nBehaviors];
void HMMTest(sState sCurrent, tBehavior behavior);
void printReport(void);

Behavior behaviorObj = Behavior();
sState sCurrent  = statesArray[sHappy];

void setup() {

    Serial.begin(9600);
    behaviorObj.setSerial(&Serial);
}

void loop() {

    for(uint16_t i = 0; i <10000;i++){
        sCurrent = nextState(sCurrent);
        printData(sCurrent);
        tBehavior selectedBehavior = runBehavior(sCurrent, behaviorObj);
        HMMTest(sCurrent, selectedBehavior);
        delay(5000); //You should remove the delay if testing the probabilities
    }

    printReport();
    while(1);
}

void printReport(void){

    uint32_t nTotal = 0;
    uint32_t  nTStates[nStates] = {0, 0, 0};

    Serial.println("~~~ PRINTING REPORT ~~~");
    Serial.println("Ocurrence Matrix State vs Behavior");
    for(int i = 0; i <nStates; i++){
        for(int j = 0; j < nBehaviors; j++){
            Serial.print(" ");Serial.print(HMMTableTests[i][j]);
            nTStates[i] += HMMTableTests[i][j];
            nTotal += HMMTableTests[i][j];
        }
        Serial.println();
    }
    Serial.println();
    Serial.print("nTotal: "); Serial.println(nTotal);
    Serial.println();

    for(int i = 0; i <nStates; i++){
        Serial.println();
        Serial.print(statesStr[i]);Serial.print(" Total: "); Serial.print(nTStates[i]);
        Serial.print(" Prob: "); Serial.println((float)nTStates[i]/nTotal);
        Serial.print("Prob Behaviors: ");
        for(int j = 0; j < nBehaviors; j++){
            Serial.print((float)HMMTableTests[i][j]/nTStates[i]);
            Serial.print(" ");
        };
        Serial.println();
    }
    return;
}

void HMMTest(sState sCurrent, tBehavior behavior){
    HMMTableTests[sCurrent.state][behavior]++;
}
