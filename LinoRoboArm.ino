#include "LinoRoboArm.h"




/* ================================================================================================================================= */




uint16_t maxPos[6]  = {360, 360, 360, 360, 360, 360};
uint16_t minPos[6]  = {  0,   0,   0,   0,   0,   0};
uint16_t initPos[6] = { 90,  90,  90,  90,  90,  90};
LinoRoboArm arm = LinoRoboArm(minPos, maxPos);


String inputString  = "";
bool stringComplete = false;




/* ================================================================================================================================= */




/**
 *  @brief Parse input from string to specified servo position.
 *  @param command Command string.
 *  @return True if input valid, False if invalid.
 */
void parseInput(String command, int parsed[2]) {
    parsed[0] = -1;
    int servoID = command[0] - 48;
    if(servoID >= 0 && servoID <= arm.GetJoints()) {
        int newPos = command.substring(1,4).toInt();
        parsed[0] = servoID;
        parsed[1] = newPos;
    }
}



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
    arm.SetServos(initPos);
}





void loop() {
    if(stringComplete) {
        Serial.print("Comando: ");
        Serial.print(inputString);

        int parsedInput[2];
        parseInput(inputString, parsedInput);
        if(parsedInput[0] > -1)
            arm.SetServo(parsedInput[0], parsedInput[1]);

        Serial.print("Posizioni correnti: ");
        Serial.println(arm.PrintPositions());

        inputString = "";
        stringComplete = false;
    }
}
