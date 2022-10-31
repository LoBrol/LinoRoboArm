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
        uint16_t checkValidPos(uint8_t servoID, uint16_t newPos);
        bool parseInput(String command);
        void printPositions();
}




/* ================================================================================================================================= */





/**
 * @brief LinoRoboArm constructor, initialize Adafruit_PWMServoDriver library
 * @return null
 */
LinoRoboArm::LinoRoboArm() {
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
}





/**
 * @brief LinoRoboArm constructor, initialize Adafruit_PWMServoDriver library
 * @param newPositions[] starting position for all the servos
 * @return null
 */
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
 *  @brief Check if the position of a servo is within acceptable range.
 *  @param servoID Servo ID (index).
 *  @param newPos Servo new position.
 *  @return acceptable position.
 */
uint16_t LinoRoboArm::checkValidPos(uint8_t servoID, uint16_t newPos) {
    if (newPos < minPos[servoID]) newPos = minPos[servo];
    if (newPos > maxPos[servoID]) newPos = maxPos[servo];
    return newPos;
}





/**
 *  @brief Parse input from string to specified servo position, and (if correct) save to curPos array.
 *  @param command command string
 *  @return True if input valid, False if invalid.
 */
bool LinoRoboArm::parseInput(String command) {
    bool inputValid = false;
    uint8_t servo = command.charAt(0).toInt();
    if(servo <= 5) {
        inputValid = true;
        uint16_t newPos = command.substring(1,4).toInt();
        curPos[servo] = checkPos(servo, newPos);
    }
    return inputValid;
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
