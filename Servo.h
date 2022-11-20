#pragma once




/* ================================================================================================================================= */





class Servo {
    private:
        uint8_t currentPosition;                            // Current position in Degree
        uint8_t minimumPosition;                            // Minimum position in Degree
        uint8_t maximumPosition;                            // Maximum position in Degree
    
    public:
        Servo();
        Servo(uint8_t min, uint8_t max);
        void SetMinMax(uint8_t min, uint8_t max);
        void SetServo(uint8_t val);
        uint8_t GetServo();
        uint8_t GetMin();
        uint8_t GetMax();
        uint8_t CheckValid(uint8_t val);
};




/* ================================================================================================================================= */




/**
 * @brief Servo constructor.
 * @return null
 */
Servo::Servo() {}

/**
 * @brief Servo constructor, set minimum and maximum limit.
 * @param min Minimum limit.
 * @param max Maximum limit.
 * @return null
 */
Servo::Servo(uint8_t min, uint8_t max) {
    minimumPosition = min;
    maximumPosition = max;
}




/* ================================================================================================================================= */




/**
 * @brief Set Minimum and Maximum limits.
 * @param min Minimum limit (degree).
 * @param max Maximum limit (degree).
 */
void Servo::SetMinMax(uint8_t min, uint8_t max) {
    minimumPosition = min;
    maximumPosition = max; 
}





/**
 * @brief Set Servo position.
 * @param val New position value.
 * @return null
 */
void Servo::SetServo(uint8_t val) {
    currentPosition = CheckValid(val);
}




/**
 * @brief Get Servo position.
 * @return Current position.
 */
uint8_t Servo::GetServo() {
    return currentPosition;
}




/* ================================================================================================================================= */




uint8_t Servo::GetMin() {
    return minimumPosition;
}





uint8_t Servo::GetMax() {
    return maximumPosition;
}




/* ================================================================================================================================= */




/**
 * @brief Check if the value is valid, if not it will sostitute with limit.
 * @param val Position value.
 * @return null
 */
uint8_t Servo::CheckValid(uint8_t val) {
    if(val < minimumPosition) val = minimumPosition;
    if(val > maximumPosition) val = maximumPosition;
    return val;
}