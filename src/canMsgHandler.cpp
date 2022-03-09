#include "canMsgHandler.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> myCan;

void initializeCAN(uint8_t canLine)
{
    myCan.begin(); // needed to initialize the CAN object (must be first method called)
    myCan.setBaudRate(BAUD_RATE); // sets baud rate

    myCan.setMaxMB(MAX_MB_NUM);
    myCan.enableFIFO(); // enables the FIFO operation mode, where all received messages are received and accessed via a queue
    myCan.enableFIFOInterrupt(); // enables interrupts to be used with FIFO
    myCan.onReceive(incomingCANCallback); // sets the callback for received messages
    myCan.mailboxStatus(); // prints out mailbox config information
}


int sendMessage(uint32_t id, uint8_t len, const uint8_t *buf)
{
CAN_message_t msg;
msg.id = id;
msg.len = len;
uint8_t *buf1;

    for (int i = 0; i < 8; i++) {
        if (i < len)
        {
            buf1 = const_cast<uint8_t*>(buf + i);
            msg.buf[i] = *buf1;
        }
        else
        {
            msg.buf[i] = 0; // copies buf to message, padding with 0s if length isn't 8
        }
    }

    return myCan.write(msg);
}

void canHandler_CANMSG_CONFIGUREADDR(const CAN_message_t &msg){
    EEPROM.write(msg.buf[0],msg.buf[1]);
    readEEPROMAddrs();
}

void readEEPROMAddrs()
{
    canmsgAddr.BMSSHUTDOWN = EEPROM.read(BMSSHUTDOWN);
    canmsgAddr.BMSDTCSTATUS = EEPROM.read(BMSDTCSTATUS);
    canmsgAddr.SET_INVERTER = EEPROM.read(SET_INVERTER);
    canmsgAddr.SET_CARDIRECTION = EEPROM.read(SET_CARDIRECTION);
    canmsgAddr.SET_BRAKELIGHT = EEPROM.read(SET_BRAKELIGHT);
    canmsgAddr.ERR_BRAKESWITCH = EEPROM.read(ERR_BRAKESWITCH);
    canmsgAddr.ERR_PEDALSENSOR = EEPROM.read(ERR_PEDALSENSOR);
    canmsgAddr.CARACCELERATION = EEPROM.read(CARACCELERATION);
    canmsgAddr.BRAKEFLUIDPRESSURE = EEPROM.read(BRAKEFLUIDPRESSURE);
    canmsgAddr.COOLINGFLOWRATE = EEPROM.read(COOLINGFLOWRATE);
    canmsgAddr.GPSDATA = EEPROM.read(GPSDATA);
    canmsgAddr.DIFFTEMP = EEPROM.read(DIFFTEMP);
}

/**
 * @brief Processes all CAN messages
 * @note  ID filtering should happen beforehand, maybe add relevent ID's to each .cpp file?
 * 
 * @param msg 
 */
void incomingCANCallback(const CAN_message_t &msg)
{
    if(!SDWrite())
    {
        Serial.println("Error logging to SD Card!");
    }

    switch(msg.id)
    {
        //Predefined CAN ID's
        case CANMSG_CONFIGUREADDR           :
            canHandler_CANMSG_CONFIGUREADDR(msg);
            break;
        case CANMSG_ACCELERATIONCTRLINFO    :
            canHandler_CANMSG_ACCELERATIONCTRLINFO(msg);
            break;
        case CANMSG_MOTORTEMP1              :
            canHandler_CANMSG_MOTORTEMP1(msg);          //Do all motor temp messages get handled the same way? if so we can make all them go to the same case
            break;
        case CANMSG_MOTORTEMP2              :
            canHandler_CANMSG_MOTORTEMP2(msg);
            break;
        case CANMSG_MOTORETEMP3             :
            canHandler_CANMSG_MOTORETEMP3(msg);
            break;
        case CANMSG_MOTORMOTION             :
            canHandler_CANMSG_MOTORMOTION(msg);
            break;
        case CANMSG_MOTORCURRENT            :
            canHandler_CANMSG_MOTORCURRENT(msg);
            break;
        case CANMSG_MOTORVOLTAGE            :
            canHandler_CANMSG_MOTORVOLTAGE(msg);
            break;
        case CANMSG_MCVEHICLESTATE          :
            canHandler_CANMSG_MCVEHICLESTATE(msg);
            break;
        case CANMSG_ERR_MCFAULT             :
            canHandler_CANMSG_ERR_MCFAULT(msg);
            break;
        case CANMSG_MOTORTORQUETIMER        :
            canHandler_CANMSG_MOTORTORQUETIMER(msg);
            break;
        case CANMSG_BMSSTATUS2              :
            canHandler_CANMSG_BMSSTATUS2(msg);
            break;
        case CANMSG_BMSCHARGEDISCHARGE      :
            canHandler_CANMSG_BMSCHARGEDISCHARGE(msg);
            break;
        case CANMSG_MC_BMS_INTEGRATION      :
            canHandler_CANMSG_MC_BMS_INTEGRATION(msg);
            break;
        case CANMSG_CHARGER_TO_BMS          :
            canHandler_CANMSG_CHARGER_TO_BMS(msg);
            break;
        case CANMSG_BMS_TO_CHARGER          :
            canHandler_CANMSG_BMS_TO_CHARGER(msg);
            break;
        default:
            if (msg.id == canmsgAddr.GPSDATA)
            {
                canHandler_CANMSG_GPSDATA(msg);
            }
            else if (msg.id == canmsgAddr.CARACCELERATION)
            {
                canHandler_CANMSG_CARACCELERATION(msg);
            }
            else if (msg.id == canmsgAddr.BRAKEFLUIDPRESSURE)
            {
                canHandler_CANMSG_BRAKEFLUIDPRESSURE(msg);
            }
            else if (msg.id == canmsgAddr.BMSSHUTDOWN)
            {
                canHandler_CANMSG_BMSSHUTDOWN(msg);
            }
            else if (msg.id == canmsgAddr.SET_INVERTER)
            {
                canHandler_CANMSG_SET_INVERTER(msg);
            }
            else if (msg.id == canmsgAddr.COOLINGFLOWRATE)
            {
                canHandler_CANMSG_COOLINGFLOWRATE(msg);
            }
            else if (msg.id == canmsgAddr.BMSDTCSTATUS)
            {
                canHandler_CANMSG_BMSDTCSTATUS(msg);
            }
            else if (msg.id == canmsgAddr.SET_CARDIRECTION)
            {
                canHandler_CANMSG_SET_CARDIRECTION(msg);
            }
            else if (msg.id == canmsgAddr.SET_BRAKELIGHT)
            {
                canHandler_CANMSG_SET_BRAKELIGHT(msg);
            }
            else if (msg.id == canmsgAddr.ERR_BRAKESWITCH)
            {
                canHandler_CANMSG_ERR_BRAKESWITCH(msg);
            }
            else if (msg.id == canmsgAddr.ERR_PEDALSENSOR)
            {
                canHandler_CANMSG_ERR_PEDALSENSOR(msg);
            }
            else if (msg.id == canmsgAddr.DIFFTEMP)
            {
                canHandler_CANMSG_DIFFTEMP(msg);
            }
            else
            {
                Serial.println("CAN ID Invalid!");
            }
            break;
    }
}

/**************************************************************/
/**
 * @brief CAN Message Handle Commands
 * __attribute__((weak)) indicates that if the compiler doesn't find any other function with this same name, then it will default to these which just do nothing
 * This means we can use a master CAN processing command amongst all devices
 * 
 */

__attribute__((weak)) void canHandler_CANMSG_BMSSHUTDOWN          (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_BMSDTCSTATUS         (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_SET_INVERTER         (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_SET_CARDIRECTION     (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_SET_BRAKELIGHT       (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_ERR_BRAKESWITCH      (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_ERR_PEDALSENSOR      (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_CARACCELERATION      (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_BRAKEFLUIDPRESSURE   (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_COOLINGFLOWRATE      (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_GPSDATA              (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_DIFFTEMP             (const CAN_message_t &msg){return;}

//Predefined CAN Messages
__attribute__((weak)) void canHandler_CANMSG_ACCELERATIONCTRLINFO (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORTEMP1           (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORTEMP2           (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORETEMP3          (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORMOTION          (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORCURRENT         (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORVOLTAGE         (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MCVEHICLESTATE       (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_ERR_MCFAULT          (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MOTORTORQUETIMER     (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_BMSSTATUS2           (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_BMSCHARGEDISCHARGE   (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_MC_BMS_INTEGRATION   (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_CHARGER_TO_BMS       (const CAN_message_t &msg){return;}
__attribute__((weak)) void canHandler_CANMSG_BMS_TO_CHARGER       (const CAN_message_t &msg){return;}

//For SD logging in the TCU, isn't used anywhere else
__attribute__((weak)) bool SDWrite(){return true;}