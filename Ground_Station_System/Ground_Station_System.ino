#include "include/Comhand.h"
#include "include/Radio.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (set_up_GST() == 0) return;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
        Serial.println("DEBUG: loop running");
        delay(1000);
        char command_string[64];
        if (read_input(command_string, sizeof(command_string))) {
            command_t cmd;
            if (parse_command(command_string, &cmd) == 0) {
                Serial.println("DEBUG: dispatching");
                cmd_packet_t cmd_pkt; 
                if(build_packet(cmd_pkt, seqNum, &cmd)){
                  if(rf69_manager.sendtoWait((uint8_t*)&cmd_pkt, sizeof(cmd_pkt), SAT_ADDRESS)){
                    Serial.println("Sent, ACK received");
                  }
                  else{
                    Serial.println("ERROR: no ACK from satellite");
                  }
                }
                else{
                  Serial.println("ERROR: Unable to build Command Packet");
                }
            } else {
                Serial.println("ERROR: Invalid Command");
            }
        }else{
            Serial.println("ERROR: unable to read raw input");
        }
    }
    if(rf69_manager.available()) {
      uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);
      uint8_t from;

      if(rf69_manager.recvfromAck(buf, &len, &from) && len == sizeof(resp_packet_t)) {
            resp_packet_t* resp = (resp_packet_t*)buf;
            Serial.print("SAT seq "); Serial.print(resp->seq);
            Serial.print(": ");       Serial.println(status_text(resp->status));
      }
    }
}

// ****** input reading without radio ****** //
/*
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
        Serial.println("DEBUG: loop running");
        delay(1000);
        char command_string[64];
        if (read_input(command_string, sizeof(command_string))) {
            command_t cmd;
            if (parse_command(command_string, &cmd) == 0) {
                Serial.println("DEBUG: dispatching");
                int input = commhand_mock(&cmd);
                handle_commhand(input);
            } else {
                Serial.println("ERROR: Invalid Command");
            }
        }else{
            Serial.println("ERROR: unable to read raw input");
        }
        

    }
}
*/