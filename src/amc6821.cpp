#include "amc6821.h"

/**
 * @brief Construct a new AMC6821::AMC6821 object, verify functionality, set PWM duty cycle to 0, and retrieve current pwm characteristics
 * 
 */
AMC6821::AMC6821()
{
    if(verifyFunctionality())
    {
        setDutyCycle(0);
        enablePWM(1);
        getCharacteristics();
        return;
    }
    Serial.println("~~~~~~~~~~~~~~~~WARNING: Unable to verify functionality of ADXL312~~~~~~~~~~~~~~~~~~~~~~~");
    return;
}


AMC6821::~AMC6821(){}

/**
 * @brief Writing to the local I2C bus with the address of the AMC6821
 * 
 * @param cmd 
 * @param numBytes 
 */
void AMC6821::AMC6821write(uint8_t *cmd, uint8_t numBytes)
{

}

/**
 * @brief Requesting data to read in from the AMC6821
 * 
 * @param msg 
 * @param numBytes 
 * @return true 
 * @return false 
 */
bool AMC6821::AMC6821read(uint8_t *msg,uint8_t numBytes)
{

}

/**
 * @brief Verify the functionality of the onboard AMC6821
 * 
 * @return true 
 * @return false 
 */
bool AMC6821::verifyFunctionality()
{

}

/**
 * @brief Toggles the PWM output
 * 
 * @param pwm_toggle 
 */
void AMC6821::enablePWM(bool pwm_toggle)
{
    uint8_t *config2 = getConfig2Reg();
    if (*config2 == NULL)
    {
        return;
    }
    uint8_t newconfig2 = pwm_toggle ? config2[0] | 0x01 : config2[0] & 0xFE;    //Setting first bit of config reg to 1 if pwm toggle, else set to 0
    setConfig2Reg(newconfig2);
}

/**
 * @brief Reading the Configuration 2 Register
 * 
 * @return uint8_t* 
 */
uint8_t *AMC6821::getConfig2Reg()
{
    uint8_t cmd[1] = {AMC6821_CONFIG2_REG};
    uint8_t msg[1];
    AMC6821write(cmd,1);
    if(AMC6821read(msg,1))
    {
        return msg;
    }
    Serial.println("ERROR: Unable to read from AMC6821 Configuration 2 Register");
    return NULL;
}

/**
 * @brief Set the Configuration 2 Register
 * 
 * @param config 
 */
void AMC6821::setConfig2Reg(uint8_t config)
{
    uint8_t cmd[2] = {AMC6821_CONFIG2_REG, config};
    AMC6821write(cmd,2);
    return;
}

/**
 * @brief Toggles the Fan Spin Up mode for PWM output
 * 
 * @param fanspinup_toggle 
 */
void AMC6821::enableFanSpinup(bool fanspinup_toggle)
{

}

/**
 * @brief Sets the duty cycle of the PWM output
 * 
 * @param dutycycle 
 */
void AMC6821::setDutyCycle(uint8_t dutycycle)
{

}

/**
 * @brief Sets the characteristics of the characteristics register for PWM operation
 * 
 * @param fanspinuptime 
 * @param pwmfreq 
 */
void AMC6821::setCharacteristics(fanspinuptime_t fanspinuptime, pwmfreq_t pwmfreq)
{

}

/**
 * @brief Retrieves the current characteristics for PWM operation
 * 
 */
void AMC6821::getCharacteristics()
{
    uint8_t cmd[1] = {AMC6821_CHARACTERISTICS_REG};
    AMC6821write(cmd,1);
    if(AMC6821read(characteristicsmsg.msg,1))
    {
        return;
    }
    Serial.println("ERROR: Unable to read from AMC6821 Characteristics Register");
    return;
}