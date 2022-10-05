#include <Arduino.h>
#include "nerduino.h"

NERDUINO NERduino;


NERDUINO::NERDUINO()
{
    Wire.begin();
    Serial.begin(57600);
    SPI1.begin();
    SPI2.begin();
}


NERDUINO::~NERDUINO(){}


bool NERDUINO::begin()
{
    adxl312 = ADXL312();
    //amc6821 = AMC6821();
    sht30 = SHT30();
}


void NERDUINO::getADXLdata(XYZData_t *xyzbuf, uint8_t numReadings)
{
    uint8_t *msg = new uint8_t[6];
    for(uint8_t i=0;i<numReadings;i++)
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


void NERDUINO::getSHTdata(HumidData_t *humidbuf, uint8_t numReadings)
{
    uint8_t *msg = new uint8_t[6];
    for(uint8_t i=0;i<numReadings;i++)
    {
        sht30.getTempHumid(msg);

        humidbuf[i].TempData.rawdata[0]  = msg[1];
        humidbuf[i].TempData.rawdata[1]  = msg[0];
        humidbuf[i].HumidData.rawdata[0] = msg[4];
        humidbuf[i].HumidData.rawdata[1] = msg[3];
    }

    delete[] msg;
}


void NERDUINO::writeSPILine1(uint8_t *value, uint8_t numBytes) 
{
  SPI1.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));   
 
  digitalWrite(SPI1_CS,LOW);
for(uint8_t i=0; i<numBytes;i++)
    {
        SPI1.transfer(value[i]);
    }
 
  digitalWrite(SPI1_CS,HIGH);
  
  SPI1.endTransaction(); 
}


void NERDUINO::writeSPILine2(uint8_t *value, uint8_t numBytes) 
{
  SPI2.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
 
  digitalWrite(SPI2_CS,LOW);
  for(uint8_t i=0; i<numBytes;i++)
    {
        SPI2.transfer(value[i]);
    }
 
  digitalWrite(SPI2_CS,HIGH);
  
  SPI2.endTransaction();
}


void NERDUINO::readSPILine1(uint8_t *msg, uint8_t numBytes)
{

SPI1.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

digitalWrite(SPI1_CS, LOW);
for(uint8_t i=0; i<numBytes;i++)
    {
        SPI1.transfer(0x00);
        msg[i] = SPI1.transfer(0x00);
    }

    Serial.print(*msg);
}

void NERDUINO::readSPILine2(uint8_t *msg, uint8_t numBytes)
{

SPI1.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

digitalWrite(SPI2_CS, LOW);
for(uint8_t i=0; i<numBytes;i++)
    {
        SPI2.transfer(0x00);
        msg[i] = SPI2.transfer(0x00);
    }

    Serial.print(*msg);
}