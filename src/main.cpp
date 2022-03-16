#include "nerduino.h"
#include "canMsgHandler.h"

void canHandler_CANMSG_BMSSHUTDOWN(const CAN_message_t &msg)
{
  Serial.println("Message Received!");
}

nerduino nerd;

void setup() {

}

void loop()
{
  XYZData_t xyzbuf[NUM_ADXL312_SAMPLES];
  HumidData_t humidbuf[NUM_SHT30_SAMPLES];

  nerd.getADXLdata(xyzbuf, NUM_ADXL312_SAMPLES);
  Serial.println("Accelerometer Data:");
  for(uint8_t i=0; i<NUM_ADXL312_SAMPLES; i++)
  {
    Serial.print(xyzbuf[i].XData.data);
    Serial.print("\t");
    Serial.print(xyzbuf[i].YData.data);
    Serial.print("\t");
    Serial.print(xyzbuf[i].ZData.data);
    Serial.print("\t");
    Serial.println();
  }
 
  Serial.println("Humidity Data:");
  nerd.getSHTdata(humidbuf);

  Serial.println("cycle...");

  delay(500);
}