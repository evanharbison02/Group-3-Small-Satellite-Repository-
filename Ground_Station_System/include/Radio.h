#ifndef RADIO_H
#define RADIO_H

#include "include/Types.h"
#include "include/Comhand.h"
#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

// ******* Pin Assignment for Radio ******* //
#define RFM69_CS    5 //15
#define RFM69_G0    2 // 4  
#define RFM69_RST   4 //32  
#define SCK         18 //14
#define MISO        19 // 12
#define MOSI        23 //13

// ******* Information for Radio Object ******* //
#define RF69_FREQ 433.0
#define GST_ADDRESS 0x01
#define SAT_ADDRESS 0x02

// ******* Information for packets ******* //
#define MAX_ARGS 2 
extern uint8_t seqNum;

enum status_code : uint8_t {
    STATUS_OK = 0,
    STATUS_BAD_LEN,
    STATUS_BAD_CMD,
    STATUS_BAD_AXIS,
    STATUS_BAD_DIR,
    STATUS_BAD_MODE,
    STATUS_INTERNAL
};

// the commmad packet to be sent to the SAT
typedef struct{
    uint8_t seq;
    uint8_t cmd;
    uint8_t args[MAX_ARGS]; 
}cmd_packet_t;

// the respone packet to be send back as an ack 
typedef struct{
    uint8_t type;      // MSG_RESPONSE
    uint8_t seq;
    uint8_t status;
    uint8_t result;
}resp_packet_t;

// a packet used for alerting the ground station of an issue with the Sat
/*
typedef struct{
    uint8_t type;      // MSG_ALERT
    uint8_t code;      // alert_code
    uint8_t value;     // e.g. battery percent
}alert_packet_t;
*/

// used to ensure that the command packet no larger then 4 bytes  
static_assert(sizeof(cmd_packet_t) == 2 + MAX_ARGS, "cmd_packet_t has padding");

extern RH_RF69 rf69;
extern RHReliableDatagram rf69_manager;

const char* status_text(uint8_t pack_stat);

int set_up_GST( void );

int set_up_SAT( void );

bool build_packet(cmd_packet_t& pkt, uint8_t& seqNum, const command_t *cmd);

uint8_t execute(const cmd_packet_t& p, uint8_t& result);

#endif