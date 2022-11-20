#include "LinoRoboArm.h"





/* ================================================================================================================================= */





uint8_t maxPos[6]  = {360, 360, 360, 360, 360, 360};
uint8_t minPos[6]  = {  0,   0,   0,   0,   0,   0};
uint8_t initPos[6] = { 90,  90,  90,  90,  90,  90};
LinoRoboArm arm = LinoRoboArm(minPos, maxPos);
String inputString  = "";
bool stringComplete = false;





/* ================================================================================================================================= */





void serialEvent() {
    while(Serial.available()) {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if(inChar == '\n') stringComplete = true;
    }
}





void setup() {
    Serial.begin(115200);
}





void loop() {
    if(stringComplete) {
        Serial.print("Comando: ");
        Serial.println(inputString);

        arm.parseInput(inputString);

        Serial.print("Posizioni correnti: ");
        arm.PrintPositions();
        Serial.println();

        inputString = "";
        stringComplete = false;
    }
}
