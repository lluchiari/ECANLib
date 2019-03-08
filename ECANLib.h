#ifndef _ECAN_LIB_
#define _ECAN_LIB_

//////////////////////////////////////////////////////////////////////////
// CAN_OP_MODE
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_MODE_BITS   = 0xE0,   // Use this to access opmode  bits
    _CAN_MODE_NORMAL = 0x00,
    _CAN_MODE_SLEEP  = 0x20,
    _CAN_MODE_LOOP   = 0x40,
    _CAN_MODE_LISTEN = 0x60,
    _CAN_MODE_CONFIG = 0x80;

//////////////////////////////////////////////////////////////////////////
// CAN_CONFIG_FLAGS
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_CONFIG_DEFAULT         = 0xFF,   // 11111111

    _CAN_CONFIG_PHSEG2_PRG_BIT  = 0x01,
    _CAN_CONFIG_PHSEG2_PRG_ON   = 0xFF,   // XXXXXXX1
    _CAN_CONFIG_PHSEG2_PRG_OFF  = 0xFE,   // XXXXXXX0

    _CAN_CONFIG_LINE_FILTER_BIT = 0x02,
    _CAN_CONFIG_LINE_FILTER_ON  = 0xFF,   // XXXXXX1X
    _CAN_CONFIG_LINE_FILTER_OFF = 0xFD,   // XXXXXX0X

    _CAN_CONFIG_SAMPLE_BIT      = 0x04,
    _CAN_CONFIG_SAMPLE_ONCE     = 0xFF,   // XXXXX1XX
    _CAN_CONFIG_SAMPLE_THRICE   = 0xFB,   // XXXXX0XX

    _CAN_CONFIG_MSG_TYPE_BIT    = 0x08,
    _CAN_CONFIG_STD_MSG         = 0xFF,   // XXXX1XXX
    _CAN_CONFIG_XTD_MSG         = 0xF7,   // XXXX0XXX

    _CAN_CONFIG_DBL_BUFFER_BIT  = 0x10,
    _CAN_CONFIG_DBL_BUFFER_ON   = 0xFF,   // XXX1XXXX
    _CAN_CONFIG_DBL_BUFFER_OFF  = 0xEF,   // XXX0XXXX

    _CAN_CONFIG_MSG_BITS        = 0x60,
    _CAN_CONFIG_ALL_MSG         = 0xFF,   // X11XXXXX
    _CAN_CONFIG_VALID_XTD_MSG   = 0xDF,   // X10XXXXX
    _CAN_CONFIG_VALID_STD_MSG   = 0xBF,   // X01XXXXX
    _CAN_CONFIG_ALL_VALID_MSG   = 0x9F;   // X00XXXXX

//////////////////////////////////////////////////////////////////////////
// CAN_TX_MSG_FLAGS
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_TX_PRIORITY_BITS = 0x03,
    _CAN_TX_PRIORITY_0    = 0xFC,   // XXXXXX00
    _CAN_TX_PRIORITY_1    = 0xFD,   // XXXXXX01
    _CAN_TX_PRIORITY_2    = 0xFE,   // XXXXXX10
    _CAN_TX_PRIORITY_3    = 0xFF,   // XXXXXX11

    _CAN_TX_FRAME_BIT    = 0x08,
    _CAN_TX_STD_FRAME    = 0xFF,   // XXXXX1XX
    _CAN_TX_XTD_FRAME    = 0xF7,   // XXXXX0XX

    _CAN_TX_RTR_BIT      = 0x40,
    _CAN_TX_NO_RTR_FRAME = 0xFF,   // X1XXXXXX
    _CAN_TX_RTR_FRAME    = 0xBF;    // X0XXXXXX

//////////////////////////////////////////////////////////////////////////
// CAN_RX_MSG_FLAGS
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_RX_FILTER_BITS  = 0x07,  // Use this to access filter bits
    _CAN_RX_FILTER_1     = 0x00,
    _CAN_RX_FILTER_2     = 0x01,
    _CAN_RX_FILTER_3     = 0x02,
    _CAN_RX_FILTER_4     = 0x03,
    _CAN_RX_FILTER_5     = 0x04,
    _CAN_RX_FILTER_6     = 0x05,
    _CAN_RX_OVERFLOW     = 0x08,  // Set if Overflowed else cleared
    _CAN_RX_INVALID_MSG  = 0x10,  // Set if invalid else cleared
    _CAN_RX_XTD_FRAME    = 0x20,  // Set if XTD message else cleared
    _CAN_RX_RTR_FRAME    = 0x40,  // Set if RTR message else cleared
    _CAN_RX_DBL_BUFFERED = 0x80;  // Set if this message was hardware double-buffered

//////////////////////////////////////////////////////////////////////////
// CAN_MASK
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_MASK_B1 = 0,
    _CAN_MASK_B2 = 1;

//////////////////////////////////////////////////////////////////////////
// CAN_FILTER
//////////////////////////////////////////////////////////////////////////

const char
    _CAN_FILTER_B1_F1 = 0,
    _CAN_FILTER_B1_F2 = 1,
    _CAN_FILTER_B2_F1 = 2,
    _CAN_FILTER_B2_F2 = 3,
    _CAN_FILTER_B2_F3 = 4,
    _CAN_FILTER_B2_F4 = 5;

//////////////////////////////////////////////////////////////////////////
// CAN_TX_IDLE_LEVEL
//////////////////////////////////////////////////////////////////////////

const char 
    _CAN_DRIVE_HIGH_STATE_ENABLE = 0x00,
    _CAN_DRIVE_HIGH_STATE_DISABLE = 0x01;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void ECANInitialize(char SJW, char BRP, char PHSEG1, char PHSEG2, char PROPSEG, char CAN_CONFIG_FLAGS);

void ECANSetBaudRate(char SJW, char BRP, char PHSEG1, char PHSEG2, char PROPSEG, char CAN_CONFIG_FLAGS);

/**
 * @brief Sets ECAN to requested mode, i.e. copies mode to CANSTAT. Parameter mode needs to be one of CAN_OP_MODE constants (see CAN constants).
    Parameter wait_flag needs to be either 0 or 0xFF:
     - If set to 0xFF, this is a blocking call – the function won’t “return” until the requested mode is set. 
     - If 0, this is a non-blocking call. It does not verify if CAN module is switched to requested mode or not. 
       Caller must use CANGetOperationMode to verify correct operation mode before performing mode specific operation.
 * @param mode
 * @param wait_flag 
 */
void ECANSetOperationMode(unsigned short mode, unsigned short wait_flag);


void ECANSetMask(char CAN_MASK, long value, char CAN_CONFIG_FLAGS);

void ECANSetFilter(char CAN_FILTER, long value, char CAN_CONFIG_FLAGS);


/** 
 * @brief This function sets the state of CANTX pin when recessive.
 * @param driveHighState State of the CANTX pin. Valid values:
 *  - CAN_DRIVE_HIGH_STATE_ENABLE: CANTX pin will drive VDD when recessive. 
        Use it when using a differential bus to avoid signal crosstalk in CANTX from other nearby pins.
 *  - _CAN_DRIVE_HIGH_STATE_DISABLE: CANTX pin will be tri-state when recessive.
 * @req Microcontroller must be connected to CAN transceiver (MCP2551 or similar) which is connected to CAN bus.
 */
void ECANSetTxIdleLevel(char driveHighState);
    


void ECANRead(long *id, char *data, char *datalen, char *CAN_RX_MSG_FLAGS);


/**
 * 
 * @param id is CAN message identifier. Only 11 or 29 bits may be used depending on message type (standard or extended) 
 * @param data is array of bytes up to 8 bytes in length 
 * @param datalen is data length from 1–8 
 * @param CAN_TX_MSG_FLAGS is value formed from constants (see CAN constants) 
 */
void ECANWrite(long id, char *data, char datalen, char CAN_TX_MSG_FLAGS);


#endif