#include "include/Radio.h"
#include <string.h>
#include <stdlib.h>

uint8_t seqNum = 0;
uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };


RH_RF69 rf69(RFM69_CS, RFM69_G0);
RHReliableDatagram rf69_manager(rf69, SAT_ADDRESS);

const char* status_text(uint8_t pack_stat) {
    switch (pack_stat) {
        case STATUS_OK:       return "OK";
        case STATUS_BAD_LEN:  return "bad packet length";
        case STATUS_BAD_CMD:  return "unknown command";
        case STATUS_BAD_AXIS: return "invalid axis";
        case STATUS_BAD_DIR:  return "invalid direction";
        default:              return "internal error";
    }
}    

int set_up_GST( void ){
    SPI.begin(SCK, MISO, MOSI, RFM69_CS);
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);

      // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);

    if (!rf69_manager.init()) {
        Serial.println("RFM69 radio init failed");
        return 0; 
    }
    Serial.println("RFM69 radio init OK!");
    
    if (!rf69.setFrequency(RF69_FREQ)) {
        Serial.println("setFrequency failed");
    }
    rf69.setTxPower(20, true);
    rf69.setEncryptionKey(key);

    Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
    return 1;
}

int set_up_SAT( void ){

    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);
    // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);

    if (!rf69_manager.init()) {
        Serial.println("RFM69 radio init failed");
        return 0;
    }
    Serial.println("RFM69 radio init OK!");

    if (!rf69.setFrequency(RF69_FREQ)) {
        Serial.println("setFrequency failed");
    }
    rf69.setTxPower(20, true);
    rf69.setEncryptionKey(key);

    Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
    return 1;
}

bool build_packet(cmd_packet_t& pkt, uint8_t& seqNum, const command_t *cmd){
    if(cmd == nullptr) return false;
    
    pkt.seq = seqNum++;
    pkt.cmd = static_cast<uint8_t>(cmd->cmd);
    for(int i = 0; i < MAX_ARGS; i++) pkt.args[i] = static_cast<uint8_t>(cmd->args[i]);

    return true;
}

uint8_t execute(const cmd_packet_t& p, uint8_t& result) {
    command_t c;
    c.cmd  = (command_id)p.cmd;
    for (int i = 0; i < MAX_ARGS; i++) c.args[i] = (argument_id)p.args[i];

    switch (c.cmd) {
        case CMD_RUN:
            if (c.args[0] < ARG_X || c.args[0] > ARG_Z)       return STATUS_BAD_AXIS;
            if (c.args[1] != ARG_CC && c.args[1] != ARG_CW
                && c.args[1] != ARG_NONE)                  return STATUS_BAD_DIR;
            break;
        case CMD_STOP:
            if (c.args[0] != ARG_NONE && (c.args[0] < ARG_X || c.args[0] > ARG_Z))
                                                        return STATUS_BAD_AXIS;
            break;
        case CMD_HELP:
            break;
        default:
            return STATUS_BAD_CMD;
    }
    result = commhand_mock(&c);   // run the wheel/magnetorquer logic
    return STATUS_OK;
}


