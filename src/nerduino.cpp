#include <Arduino.h>
#include "nerduino.h"

nerduino::nerduino()
{
    Wire.begin();
    Serial.begin(9600);
}

nerduino::~nerduino(){}


void nerduino::getADXLdata(XYZData_t *xyzbuf, uint8_t numReadings)
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


void nerduino::getSHTdata(HumidData_t *humidbuf, uint8_t numReadings)
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
    float cTemp = ((((msg[0] * 256.0) + msg[1]) * 175) / 65535.0) - 45;
    float fTemp = (cTemp * 1.8) + 32;
    float humidity = ((((msg[3] * 256.0) + msg[4]) * 100) / 65535.0);
    Serial.print("Temperature C: ");
    Serial.print(cTemp);
    Serial.println(" C");
    Serial.print("Temperature F: ");
    Serial.print(fTemp);
    Serial.println(" F");
    Serial.print("Relative Humidity: ");
    Serial.print(humidity);
    Serial.println(" %RH");
    Serial.println("~~~~~~~~~~~");

    delete[] msg;
}
