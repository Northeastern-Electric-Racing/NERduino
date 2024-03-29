#include "amc6821.h"
#include <Arduino.h>


AMC6821::AMC6821()
{
    
    if(verifyFunctionality())
    {
        Serial.println("AMC6821 PWM Chip connected");
        resetChip();
        delay(10);
        writeConfig(1, 0x08);
        writeConfig(2, 0x03);
        writeConfig(3, 0x02);
        writeConfig(4, 0x88);
        disableFanSpinup(true);
        getCharacteristics();
        return;
    }
    Serial.println("~~~~~~~~~~~~~~~~WARNING: Unable to verify functionality of AMC6821~~~~~~~~~~~~~~~~~~~~~~~");
    return;
    
}


AMC6821::~AMC6821(){}


void AMC6821::AMC6821write(uint8_t *cmd, uint8_t num_bytes)
{
    Wire.beginTransmission(AMC6821_I2C_ADDR);
    for(uint8_t i=0; i<num_bytes;i++)
    {
        Wire.write(cmd[i]);
    }
    Wire.endTransmission();
}


bool AMC6821::AMC6821read(uint8_t *msg,uint8_t num_bytes)
{
    Wire.requestFrom(AMC6821_I2C_ADDR, (int)num_bytes);

    if (Wire.available())
    {
        uint8_t i2cByte=0;
        while(Wire.available())
        {
            msg[i2cByte] = Wire.read();
            i2cByte++;
        }
        return true;
    }

    return false;
}


bool AMC6821::verifyFunctionality()
{
    uint8_t msg[1];
    uint8_t cmd[1]= {AMC6821_DEVID_REG};
    AMC6821write(cmd,1);
    if(AMC6821read(msg,1))
    {
        if(msg[0] == AMC6821_DEVID)
        {
            return true;
        }
        return false;
    }
    return false;
}


void AMC6821::enablePWM(bool pwm_toggle)
{
    uint8_t msg[1];
    readConfig(msg, 2);
    if (msg == NULL)
    {
        Serial.println("PWM Toggle not successful");
        return;
    }
    uint8_t newconfig2;
    if (pwm_toggle == true){
        newconfig2 = msg[0] | 0x01;
    }
    else{
        newconfig2 = msg[0] & 0xFE;
    }
    writeConfig(2, newconfig2);
}

void AMC6821::disableFanSpinup(bool fanspinup_toggle)
{
    characteristicsmsg.bitfieldmsg.fanspinup_enable = fanspinup_toggle;
    setCharacteristics();
}


void AMC6821::setFanSpinUpTime(fanspinuptime_t fanspinuptime)
{
    characteristicsmsg.bitfieldmsg.fanspinuptime = fanspinuptime;
    setCharacteristics();
}


void AMC6821::setPWMFreq(pwmfreq_t pwmfreq)
{
    characteristicsmsg.bitfieldmsg.pwmfreq = pwmfreq;
    setCharacteristics();
}


void AMC6821::setDutyCycle(uint8_t duty_cycle)
{
    uint8_t cmd[2] = {AMC6821_DUTYCYCLE_REG, duty_cycle};
    AMC6821write(cmd, 2);
    AMC6821write(cmd, 1);
}


void AMC6821::setCharacteristics()
{
    uint8_t cmd[2] = {AMC6821_CHARACTERISTICS_REG, characteristicsmsg.msg};
    AMC6821write(cmd,2);
}


void AMC6821::getCharacteristics()
{
    uint8_t cmd[1] = {AMC6821_CHARACTERISTICS_REG};
    AMC6821write(cmd,1);
    AMC6821read(&characteristicsmsg.msg, 1);
    return;
}

void AMC6821::resetChip()
{
  writeConfig(2, 0x80);
  characteristicsmsg.msg = 29;
  setCharacteristics();
}

void AMC6821::writeConfig(uint8_t config_num, uint8_t config)
{
  uint8_t cmd[2];
  cmd[1] = uint8_t(config);

  switch(config_num)
  {
    case 1:
      cmd[0] =  AMC6821_CONFIG1_REG;
      break;
    case 2:
      cmd[0] =  AMC6821_CONFIG2_REG;
      break;
    case 3:
      cmd[0] =  AMC6821_CONFIG3_REG;
      break;
    case 4:
      cmd[0] =  AMC6821_CONFIG4_REG;
      break;
    default:
      Serial.println("Unidentified Config #!");
      return;
  }
  
  AMC6821write(cmd,2);
}

void AMC6821::readConfig(uint8_t *msg, uint8_t config_num)
{
  uint8_t cmd[1];

  switch(config_num)
  {
    case 1:
        cmd[0] =  AMC6821_CONFIG1_REG;
        break;
    case 2:
        cmd[0] =  AMC6821_CONFIG2_REG;
        break;
    case 3:
        cmd[0] =  AMC6821_CONFIG3_REG;
        break;
    case 4:
        cmd[0] =  AMC6821_CONFIG4_REG;
        break;
    default:
        Serial.println("Unidentified Config #!");
        msg = NULL;
        return;
  }
  AMC6821write(cmd, 1);
  AMC6821read(msg,1);
}