/**
 * @file canMsgHandler.h
 * @author Nick DePatie
 * @brief 
 * @date 2022-03-07
 */
#ifndef CANMSGHANDLER_H
#define CANMSGHANDLER_H

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <EEPROM.h>


/*************************************************/
/**
 * CAN Settings
 */

#define BAUD_RATE 250000U
#define MAX_MB_NUM 16 // maximum number of CAN mailboxes to use
extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> myCan; // main CAN object

/*************************************************/
/**
 * CAN Addresses
 */

/**
 * @brief Specifies the locations of the CAN addresses on the EEPROM
 */
enum
{
    BMSSHUTDOWN,            
    BMSDTCSTATUS,
    SET_INVERTER,
    SET_CARDIRECTION,
    SET_BRAKELIGHT,
    ERR_BRAKESWITCH,
    ERR_PEDALSENSOR,
    CARACCELERATION,
    BRAKEFLUIDPRESSURE,
    COOLINGFLOWRATE,
    GPSDATA,
    DIFFTEMP
};

/**
 * @brief Contains all CAN addresses saved in the EEPROM
 * @note MUST BE INITIALIZED BEFORE NORMAL OPERATION
 */
struct
{
    uint8_t BMSSHUTDOWN=0;
    uint8_t BMSDTCSTATUS=0;
    uint8_t SET_INVERTER=0;
    uint8_t SET_CARDIRECTION=0;
    uint8_t SET_BRAKELIGHT=0;
    uint8_t ERR_BRAKESWITCH=0;
    uint8_t ERR_PEDALSENSOR=0;
    uint8_t CARACCELERATION=0;
    uint8_t BRAKEFLUIDPRESSURE=0;
    uint8_t COOLINGFLOWRATE=0;
    uint8_t GPSDATA=0;
    uint8_t DIFFTEMP=0;
} canmsgAddr;

/**
 * @brief Configurable CAN messages
 * @todo Move to EEPROM for CAN address configure CAN messages, probably create address struct just for this
 * @note these values will be phased out as the dynamic EEPROM configurable address method is moved in
 */

#define NUM_CONFIGURABLECANMSG      12

#define CANMSG_BMSSHUTDOWN          0x03
#define CANMSG_BMSDTCSTATUS         0x06
#define CANMSG_SET_INVERTER         0x101
#define CANMSG_SET_CARDIRECTION     0x102
#define CANMSG_SET_BRAKELIGHT       0x103
#define CANMSG_ERR_BRAKESWITCH      0x104
#define CANMSG_ERR_PEDALSENSOR      0x105
#define CANMSG_CARACCELERATION      0x300
#define CANMSG_BRAKEFLUIDPRESSURE   0x301
#define CANMSG_COOLINGFLOWRATE      0x302
#define CANMSG_GPSDATA              0x303
#define CANMSG_DIFFTEMP             0x304

//Predefined CAN Messages (cannot change)
#define CANMSG_CONFIGUREADDR        0x99
#define CANMSG_ACCELERATIONCTRLINFO 0xC0
#define CANMSG_MOTORTEMP1           0xA0
#define CANMSG_MOTORTEMP2           0xA1
#define CANMSG_MOTORETEMP3          0xA2
#define CANMSG_MOTORMOTION          0xA5
#define CANMSG_MOTORCURRENT         0xA6
#define CANMSG_MOTORVOLTAGE         0xA7
#define CANMSG_MCVEHICLESTATE       0xAA
#define CANMSG_ERR_MCFAULT          0xAB
#define CANMSG_MOTORTORQUETIMER     0xAC
#define CANMSG_BMSSTATUS2           0x6B1
#define CANMSG_BMSCHARGEDISCHARGE   0x6B0
#define CANMSG_MC_BMS_INTEGRATION   0x202
#define CANMSG_CHARGER_TO_BMS       0x18EB2440
#define CANMSG_BMS_TO_CHARGER       0x18E54024

/*******************************************************************/
/**
 * Prototype Function
 */

/**
 * @brief Sends CAN message
 * 
 * @param id 
 * @param len 
 * @param buf 
 * @return int 
 */
int sendMessage(uint32_t id, uint8_t len, const uint8_t *buf);

/**
 * @brief Processes all CAN messages
 * @note  ID filtering should happen beforehand, maybe add relevent ID's to each .cpp file?
 * 
 * @param msg 
 */
void incomingCANCallback(const CAN_message_t &msg);

/**
 * @brief Initializes a CAN object for whichever line we are choosing
 * 
 * @param canLine   which CAN transceiver to use we want to use = NOT currently being used, we will probably need this eventually if we need to broadcast at different rates
 */
void initializeCAN(uint8_t canLine);

/**
 * @brief Reads in all EEPROM values and initializes the canAddr's struct
 * 
 */
void readEEPROMAddrs();

/**
 * @brief Configures the EEPROM address of the CAN message specified by the first index of the message to the address value specified by the second index of the message
 * 
 * @param msg
 */
void canHandler_CANMSG_CONFIGUREADDR(const CAN_message_t &msg);

/***********************************************************************************/
/**
 * @brief CAN Message Handle Commands
 * __attribute__((weak)) indicates that if the compiler doesn't find any other function with this same name, then it will default to these which just do nothing
 * This means we can use a master CAN processing command amongst all devices
 * 
 */

void canHandler_CANMSG_BMSSHUTDOWN          (const CAN_message_t &msg);
void canHandler_CANMSG_BMSDTCSTATUS         (const CAN_message_t &msg);
void canHandler_CANMSG_SET_INVERTER         (const CAN_message_t &msg);
void canHandler_CANMSG_SET_CARDIRECTION     (const CAN_message_t &msg);
void canHandler_CANMSG_SET_BRAKELIGHT       (const CAN_message_t &msg);
void canHandler_CANMSG_ERR_BRAKESWITCH      (const CAN_message_t &msg);
void canHandler_CANMSG_ERR_PEDALSENSOR      (const CAN_message_t &msg);
void canHandler_CANMSG_CARACCELERATION      (const CAN_message_t &msg);
void canHandler_CANMSG_BRAKEFLUIDPRESSURE   (const CAN_message_t &msg);
void canHandler_CANMSG_COOLINGFLOWRATE      (const CAN_message_t &msg);
void canHandler_CANMSG_GPSDATA              (const CAN_message_t &msg);
void canHandler_CANMSG_DIFFTEMP             (const CAN_message_t &msg);

//Predefined CAN Messages
void canHandler_CANMSG_ACCELERATIONCTRLINFO (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORTEMP1           (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORTEMP2           (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORETEMP3          (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORMOTION          (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORCURRENT         (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORVOLTAGE         (const CAN_message_t &msg);
void canHandler_CANMSG_MCVEHICLESTATE       (const CAN_message_t &msg);
void canHandler_CANMSG_ERR_MCFAULT          (const CAN_message_t &msg);
void canHandler_CANMSG_MOTORTORQUETIMER     (const CAN_message_t &msg);
void canHandler_CANMSG_BMSSTATUS2           (const CAN_message_t &msg);
void canHandler_CANMSG_BMSCHARGEDISCHARGE   (const CAN_message_t &msg);
void canHandler_CANMSG_MC_BMS_INTEGRATION   (const CAN_message_t &msg);
void canHandler_CANMSG_CHARGER_TO_BMS       (const CAN_message_t &msg);
void canHandler_CANMSG_BMS_TO_CHARGER       (const CAN_message_t &msg);

//For SD logging in the TCU, isn't used anywhere else
bool SDWrite();

/**************************************************/

#endif