#include "LinoRoboArm.h"





/* ================================================================================================================================= */





LinoRoboArm arm;
uint16_t initPos[6] = {512, 200, 300, 512, 300, 300};
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
    arm = new LinoRoboArm(initPos);
}





void loop() {
    if(stringComplete) {
        Serial.print("Comando: ");
        Serial.println(inputString);
        arm.parseInput(inputString);
        arm.setServos();
        Serial.print("Posizioni correnti: ");
        arm.printPositions();
        Serial.println();
        inputString = "";
        stringComplete = false;
    }
}
