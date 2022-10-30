class LinoRoboArm {
    private:
        uint16_t curPos[6]  = {  0,   0,   0,   0,   0,   0};                   // Array to store Servos positions
        uint16_t maxPos[6]  = {512, 512, 512, 512, 512, 512};                   // Servos maximum positions
        uint16_t minPos[6]  = {  0,   0,   0,   0,   0,   0};                   // Servos minimum positions
        Adafruit_PWMServoDriver pwm;

    public:
        LinoRoboArm();
        LinoRoboArm(uint16_t newPositions[]);
        void setServo(uint8_t servoID, uint16_t newPos);
        void setServos(uint16_t newPositions[]);
        bool parseInput();
        uint16_t checkValidPos(uint8_t servoID, uint16_t newPos);
        void printPositions();
}




/* ================================================================================================================================= */





LinoRoboArm::LinoRoboArm() {
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);
}





LinoRoboArm::LinoRoboArm(uint16_t newPositions[]) {
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
    setServos(newPositions);
}





/* ================================================================================================================================= */





/**
 * @brief Actuate single servo with the new position store in "newPos"
 * @param servoID ID of the servo to configure
 * @param newPos PWM value (0-4096)
 * @return null
 */
void LinoRoboArm::setServo(uint8_t servoID, uint16_t newPos) {
    newPos = checkValidPos(servoID, newPos);
    pwm.setPWM(servoID, 0, newPos[servoID]);
}





/**
 *  @brief Actuate all servos from the position saved to the array.
 *  @param position 6 positions array, used to set servos postions.
 *  @return null
 */
void LinoRoboArm::setServos(uint16_t newPositions[6]) {
    for (byte i = 0; i < 6; i++){
        setServo(i, newPositions[i]);
    }
}





/* ================================================================================================================================= */





/**
 *  @brief Parse input from string to specified servo position.
 *  @return True if input valid, False if invalid.
 */
bool LinoRoboArm::parseInput() {
    bool inputValid = false;
    uint8_t servo = inputString.charAt(0) - 48;
    if(servo >= 0 && servo <= 6) {
        inputValid = true;
        uint16_t newPos = inputString.substring(1,4).toInt();
        curPos[servo] = checkPos(servo, newPos);
    }
    return inputValid;
}




/**
 *  @brief Check if the position of a servo is within acceptable range.
 *  @param servoID Servo ID (index).
 *  @param newPos Servo new position.
 *  @return acceptable position.
 */
uint16_t LinoRoboArm::checkPos(uint8_t servoID, uint16_t newPos) {
    if (pos < minPos[servo]) return minPos[servo];
    if (pos > maxPos[servo]) return maxPos[servo];
    return pos;
}





/* ================================================================================================================================= */





/**
 *  @brief Print on screen, using Serial.print, the current value of the postions of the servos.
 *  @return null
 */
void LinoRoboArm::printPositions() {
    for (byte i = 0; i < 5; i++){
        Serial.print(curPos[i]);
        Serial.print(",");
    }
    Serial.print(curPos[5]);
}