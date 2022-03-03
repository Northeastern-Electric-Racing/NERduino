#ifndef ADXL312_H
#define ADXL312_h

#include <Arduino.h>
#include <Wire.h>

//ADXL312 Accelerometer
/**
 * https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL312.pdf  --Datasheet
 * https://wiki.analog.com/resources/quick-start/adxl312_quick_start_guide          --Used for implementation
 */
#define ADXL312_I2C_ADDR                0x53    //This depends on how the address pin is wired, 0x1D with Vcc and 0x53 with Gnd
#define ADXL312_DEVID_REG               0x00
#define ADXL312_DEVID                   0xE5
#define ADXL312_POWER_CTRL_REG          0x2D
#define ADXL312_POWER_CTRL_MEASURECMD   0x08    //This tells the accelerometer to read the value, might need to change it the sleep mode if not in use
#define ADXL312_XYZDATA_REG_OFFSET      0x32    //The XYZ data registers are 0x32-0x37

class ADXL312
{
    private:
        void ADXL312write(uint8_t *msg, uint8_t numBytes);
        bool ADXL312read(uint8_t *msg,uint8_t numBytes);

    public:
        ADXL312();      //constructor
        ~ADXL312();     //destructor
        bool verifyFunctionality();
        void configureForMeasurement();
        void getXYZ(uint8_t *msg);
};

#endif