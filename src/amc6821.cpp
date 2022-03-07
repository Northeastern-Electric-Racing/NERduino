#include "amc6821.h"


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


void AMC6821::AMC6821write(uint8_t *cmd, uint8_t numBytes)
{

}


bool AMC6821::AMC6821read(uint8_t *msg,uint8_t numBytes)
{

}


bool AMC6821::verifyFunctionality()
{

}


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


void AMC6821::setConfig2Reg(uint8_t config)
{
    uint8_t cmd[2] = {AMC6821_CONFIG2_REG, config};
    AMC6821write(cmd,2);
    return;
}


void AMC6821::enableFanSpinup(bool fanspinup_toggle)
{

}


void AMC6821::setDutyCycle(uint8_t dutycycle)
{

}


void AMC6821::setCharacteristics(fanspinuptime_t fanspinuptime, pwmfreq_t pwmfreq)
{

}


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