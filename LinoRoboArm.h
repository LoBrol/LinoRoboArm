#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "Servo.h"


constexpr uint16_t MAX_PWM = 512;      // Max PWM value
constexpr uint8_t JOINTS =  6;         // Number of joints in the arm




/* ================================================================================================================================= */




class LinoRoboArm {
    private:
        Servo servos[JOINTS];
        Adafruit_PWMServoDriver pwm;

    public:
        LinoRoboArm(uint16_t mins[], uint16_t maxs[]);
        uint16_t GetJoints();
        void SetServo(uint8_t ServoID, uint16_t val);
        void SetServos(uint16_t val[]);
        void moveServo(uint8_t ServoID, uint16_t val);
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
LinoRoboArm::LinoRoboArm(uint16_t mins[], uint16_t maxs[]) {
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
uint16_t LinoRoboArm::GetJoints() {
    return JOINTS;
}





/**
 * @brief Actuate single servo with the new position.
 * @param servoID ID of the servo to configure.
 * @param val New degree values.
 * @return null
 */
void LinoRoboArm::SetServo(uint8_t ServoID, uint16_t val) {
    servos[ServoID].SetServo(val);
    moveServo(ServoID, val);
}




/**
 * @brief Actuate all the servo with the new position.
 * @param val Array of the new degree values.
 * @return null
 */
void LinoRoboArm::SetServos(uint16_t val[]) {
    for(uint8_t i = 0; i < JOINTS; i++)
        SetServo(i, val[i]);
}




/* ================================================================================================================================= */




/**
 * @brief Actuate the servo with the new position.
 * @param val Array of the new degree values.
 * @return null
 */
void LinoRoboArm::moveServo(uint8_t ServoID, uint16_t val) {
    uint16_t PWMval = map(val, 0, MAX_PWM, servos[ServoID].GetMin(), servos[ServoID].GetMax());
    pwm.setPWM(ServoID, 0, PWMval);
}




/* ================================================================================================================================= */




/**
 *  @brief Print on screen, using Serial.print, the current value of the postions of the servos.
 *  @return String with the postions, separated with a comma.
 */
String LinoRoboArm::PrintPositions() {
    String aux = "";
    for (uint8_t i = 0; i < JOINTS - 1; i++) {
        aux += servos[i].GetServo();
        aux += ",";
    }
    aux += servos[5].GetServo();
    return aux;
}
