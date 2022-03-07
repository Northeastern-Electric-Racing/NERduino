#ifndef AMC6821_H
#define AMC6821_H

#include <Arduino.h>

//AMC6821 PWM Generator
/**
 * https://www.ti.com/lit/ds/symlink/amc6821.pdf?ts=1644706226375&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FAMC6821%253Futm_source%253Dgoogle%2526utm_medium%253Dcpc%2526utm_campaign%253Dasc-sens-null-prodfolderdynamic-cpc-pf-google-wwe%2526utm_content%253Dprodfolddynamic%2526ds_k%253DDYNAMIC%2BSEARCH%2BADS%2526DCM%253Dyes%2526gclid%253DCj0KCQiA0p2QBhDvARIsAACSOOPKQVP7tfyxbaC8997ZjeHcQWZiSwAi1yblV-rFrJZ4BQS3xCwo1iYaAjmLEALw_wcB%2526gclsrc%253Daw.ds 
 * ^Datasheet
 */
#include <Wire.h> //I2C library 


#define AMC6821_I2C_ADDR                    0x18
#define AMC6821_DEVID_REG                   0x3D
#define AMC6821_DEVID                       0x21
#define AMC6821_CONFIG2_REG                 0x01


/**
 * @note Duty Cycle is variable corresponding to 1/255 increments 
 *       (0x00 corresponds to 0% duty cycle and 0xFF(255) corresponds to 100% duty cycle)
 * @ref Refer to page 40 of datasheet
 */
#define AMC6821_DUTYCYCLE_REG               0x22


/**
 * @brief PWM I2C Characteristics Command Contents  (8 bits)
 * @ref Refer to page 41 of datasheet
 *                _______________________________________________________________________________________________________________
 * bit numbers:   |            7            |      6      |           5   4   3               |            2   1   0            |
 *                |-------------------------|-------------|-----------------------------------|---------------------------------|
 * contents:      |   Fan spin up disable   |   Reserved  |   PWM Frequency(see AMC macros)   |   Spin up time(see AMC macros)  |
 *                |_________________________|_____________|___________________________________|_________________________________|
 * 
 */
#define AMC6821_CHARACTERISTICS_REG         0x20

//PWM Frequencies type
typedef enum
{
    AMC6821_CHARACTERISTICS_1KHZ,
    AMC6821_CHARACTERISTICS_10KHZ,
    AMC6821_CHARACTERISTICS_20KHZ,
    AMC6821_CHARACTERISTICS_25KHZ,          //(default) frequency for our fans
    AMC6821_CHARACTERISTICS_30KHZ,
    AMC6821_CHARACTERISTICS_40KHZ           //0x06 and 0x07 also result in 40kHz duty cycle
}pwmfreq_t;

//Fan spin up times type
typedef enum
{
    AMC6821_CHARACTERISTICS_SPINUP_02,      //02 means 0.2 seconds
    AMC6821_CHARACTERISTICS_SPINUP_04,      //04 means 0.4 seconds
    AMC6821_CHARACTERISTICS_SPINUP_06,      //...
    AMC6821_CHARACTERISTICS_SPINUP_08,
    AMC6821_CHARACTERISTICS_SPINUP_1,
    AMC6821_CHARACTERISTICS_SPINUP_2,       //(default)
    AMC6821_CHARACTERISTICS_SPINUP_4,
    AMC6821_CHARACTERISTICS_SPINUP_8 
}fanspinuptime_t;

/*********************************************************************************************/

class AMC6821
{
    private:
        void AMC6821write(uint8_t *cmd, uint8_t numBytes);
        bool AMC6821read(uint8_t *msg,uint8_t numBytes);

        //PWM characteristics bitfield
        union
        {
            uint8_t *msg;

            struct
            {
                uint8_t fanspinup_enable        :1;
                uint8_t reserved                :1;
                pwmfreq_t pwmfreq               :3;
                fanspinuptime_t fanspinuptime   :3;
            } bitfieldmsg;
        }characteristicsmsg;

    public:
        AMC6821();
        ~AMC6821();
        bool verifyFunctionality();
        void enablePWM(bool pwm_toggle);
        void enableFanSpinup(bool fanspinup_toggle);
        void setDutyCycle(uint8_t dutycycle);
        void setCharacteristics(fanspinuptime_t fanspinuptime, pwmfreq_t pwmfreq);
        void getCharacteristics();
        uint8_t *getConfig2Reg();
        void setConfig2Reg(uint8_t config);
};

#endif