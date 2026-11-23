#include "include/Radio.h"
#include <string.h>
#include <stdlib.h>

uint8_t seqNum = 0;
uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

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

