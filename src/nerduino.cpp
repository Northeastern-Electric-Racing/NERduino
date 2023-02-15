#include <Arduino.h>
#include "nerduino.h"

NERDUINO NERduino;


NERDUINO::NERDUINO()
{
    Wire.begin();
    Serial.begin(57600);
}


NERDUINO::~NERDUINO(){}


bool NERDUINO::begin()
{
    adxl312 = ADXL312();
    amc6821 = AMC6821();
    sht30 = SHT30();
}


void NERDUINO::getADXLdata(XYZData_t *xyzbuf, uint8_t num_readings)
{
    uint8_t *msg = new uint8_t[6];
    for(uint8_t i=0;i<num_readings;i++)
    {
        adxl312.getXYZ(msg);

        xyzbuf[i].XData.rawdata[0] = msg[0];
        xyzbuf[i].XData.rawdata[1] = msg[1];
        xyzbuf[i].YData.rawdata[0] = msg[2];
        xyzbuf[i].YData.rawdata[1] = msg[3];
        xyzbuf[i].ZData.rawdata[0] = msg[4];
        xyzbuf[i].ZData.rawdata[1] = msg[5];
        delay(5);
    }
    delete[] msg;
}


void NERDUINO::getSHTdata(HumidData_t *humidbuf, uint8_t num_readings)
{
    uint8_t *msg = new uint8_t[6];
    for(uint8_t i=0;i<num_readings;i++)
    {
        sht30.getTempHumid(msg);

        humidbuf[i].TempData.rawdata[0]  = msg[1];
        humidbuf[i].TempData.rawdata[1]  = msg[0];
        humidbuf[i].HumidData.rawdata[0] = msg[4];
        humidbuf[i].HumidData.rawdata[1] = msg[3];
    }

    delete[] msg;
}

void NERDUINO::setAMCDutyCycle(uint8_t duty_cycle)
{
    amc6821.setDutyCycle(duty_cycle);
}

void NERDUINO::setAMCPWMFreq(pwmfreq_t pwmfreq)
{
    amc6821.setPWMFreq(pwmfreq);
}

void NERDUINO::enableSPI1()
{
    pinMode(SPI1_CS, OUTPUT);
    digitalWrite(SPI1_CS, HIGH);        //! 1) Pull Chip Select High

    pinMode(SPI1_SCK, OUTPUT);          //! 1) Setup SCK as output
    pinMode(SPI1_MOSI, OUTPUT);         //! 2) Setup MOSI as output
    SPI.begin();
}

void NERDUINO::writeSPI1(uint8_t tx_Data[], uint8_t tx_len, SPISettings settings)
{
    SPI.beginTransaction(settings);
    for (uint8_t i = 0; i < tx_len; i++)
    {
        SPI.transfer((int8_t)tx_Data[i]);
    }
    SPI.endTransaction();
}

void NERDUINO::writereadSPI1(uint8_t tx_Data[], uint8_t tx_len, uint8_t *rx_data, uint8_t rx_len, SPISettings settings)
{
    SPI.beginTransaction(settings);
    for (uint8_t i = 0; i < tx_len; i++)
    {
        SPI.transfer(tx_Data[i]);

    }

    for (uint8_t i = 0; i < rx_len; i++)
    {
        rx_data[i] = (uint8_t)SPI.transfer(0xFF);
    }
    SPI.endTransaction();
}