#pragma once




/* ================================================================================================================================= */





class Servo {
    private:
        uint16_t currentPosition;                           // Current position in Degree
        uint16_t minimumPosition;                           // Minimum position in Degree
        uint16_t maximumPosition;                           // Maximum position in Degree
    
    public:
        Servo();
        Servo(uint16_t min, uint16_t max);
        Servo(uint16_t min, uint16_t max, uint16_t cur);
        void SetMinMax(uint16_t min, uint16_t max);
        void SetServo(uint16_t val);
        uint16_t GetServo();
        uint16_t GetMin();
        uint16_t GetMax();
        uint16_t CheckValid(uint16_t val);
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
Servo::Servo(uint16_t min, uint16_t max) {
    minimumPosition = min;
    maximumPosition = max;
}





/**
 * @brief Servo constructor, set minimum and maximum limit.
 * @param min Minimum limit.
 * @param max Maximum limit.
 * @param cur Current position.
 * @return null
 */
Servo::Servo(uint16_t min, uint16_t max, uint16_t cur) {
    minimumPosition = min;
    maximumPosition = max;
    currentPosition = CheckValid(cur);
}




/* ================================================================================================================================= */




/**
 * @brief Set Minimum and Maximum limits.
 * @param min Minimum limit (degree).
 * @param max Maximum limit (degree).
 */
void Servo::SetMinMax(uint16_t min, uint16_t max) {
    minimumPosition = min;
    maximumPosition = max; 
}





/**
 * @brief Set Servo position.
 * @param val New position value.
 * @return null
 */
void Servo::SetServo(uint16_t val) {
    currentPosition = CheckValid(val);
}




/* ================================================================================================================================= */




/**
 * @brief Get Servo position.
 * @return Current position.
 */
uint16_t Servo::GetServo() {
    return currentPosition;
}





uint16_t Servo::GetMin() {
    return minimumPosition;
}





uint16_t Servo::GetMax() {
    return maximumPosition;
}




/* ================================================================================================================================= */




/**
 * @brief Check if the value is valid, if not it will sostitute with limit.
 * @param val Position value.
 * @return null
 */
uint16_t Servo::CheckValid(uint16_t val) {
    if(val < minimumPosition) val = minimumPosition;
    if(val > maximumPosition) val = maximumPosition;
    return val;
}