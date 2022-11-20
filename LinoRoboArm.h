#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "Servo.h"


#define MAX_PWM 512
#define JOINTS 6




/* ================================================================================================================================= */




class LinoRoboArm {
    private:
        Servo servos[JOINTS];
        Adafruit_PWMServoDriver pwm;

    public:
        LinoRoboArm(uint8_t mins[], uint8_t maxs[]);
        uint8_t GetJoints();
        void SetServo(uint8_t ServoID, uint8_t val);
        void SetServos(uint8_t val[]);
        void moveServo(uint8_t ServoID, uint8_t val);
        bool parseInput(String command);
        String PrintPositions();
};




/* ================================================================================================================================= */




/**
 * @brief LinoRoboArm constructor, initialize "Adafruit_PWMServoDriver" library
 * @param mins Minimums degrees of the servors.
 * @param maxs Maximums degrees of the servors.
 * @return null
 */
LinoRoboArm::LinoRoboArm(uint8_t mins[], uint8_t maxs[]) {
    for(uint8_t i = 0; i < JOINTS; i++)
        servos[i] = Servo(mins[i], maxs[i]);
        
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
}




/* ================================================================================================================================= */




/**
 * @brief Get number of Joints in the Arm.
 * @return Number of Joints.
 */
uint8_t LinoRoboArm::GetJoints() {
    return JOINTS;
}





/**
 * @brief Actuate single servo with the new position.
 * @param servoID ID of the servo to configure.
 * @param val New degree values.
 * @return null
 */
void LinoRoboArm::SetServo(uint8_t ServoID, uint8_t val) {
    servos[ServoID].SetServo(val);
    moveServo(ServoID, val);
}




/**
 * @brief Actuate all the servo with the new position.
 * @param val Array of the new degree values.
 * @return null
 */
void LinoRoboArm::SetServos(uint8_t val[]) {
    for(uint8_t i = 0; i < JOINTS; i++)
        SetServo(i, val);
}




/* ================================================================================================================================= */




/**
 * @brief Actuate the servo with the new position.
 * @param val Array of the new degree values.
 * @return null
 */
void LinoRoboArm::moveServo(uint8_t ServoID, uint8_t val) {
    uint16_t PWMval = map(val, 0, MAX_PWM, servos[ServoID].GetMin(), servos[ServoID].GetMax());
    pwm.setPWM(ServoID, 0, PWMval);
}




/* ================================================================================================================================= */




/**
 *  @brief Parse input from string to specified servo position.
 *  @param command Command string.
 *  @return True if input valid, False if invalid.
 */
bool LinoRoboArm::parseInput(String command) {
    bool inputValid = false;
    uint8_t servoID = (int) command[0] - 48;
    if(servoID >= 0 && servoID <= 5) {
        inputValid = true;
        uint8_t newPos = command.substring(1,4).toInt();
        SetServo(servoID, newPos);
    }
    return inputValid;
}





/* ================================================================================================================================= */





/**
 *  @brief Print on screen, using Serial.print, the current value of the postions of the servos.
 *  @return String with the postions, separated with a comma.
 */
String LinoRoboArm::PrintPositions() {
    String aux = "";
    for (byte i = 0; i < 5; i++)
        aux += servos[i].GetServo() + ",";
    aux += servos[5].GetServo();
    return aux;
}