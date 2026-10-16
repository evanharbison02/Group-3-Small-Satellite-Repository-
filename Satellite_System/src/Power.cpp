#include "include/Power.h"
#include <string.h>
#include <stdlib.h>

// initialize the reading variables are globe 
globle float shuntvoltage = 0;
globle float busvoltage = 0;
globle float current_mA = 0;
globle float loadvoltage = 0;
globle float power_mW = 0;

int set_up_INA219(uint8_t SDA_Pin, uint8_t SCL_Pin){
    
    // make a new INA219 object 
    Adafruit_INA219 ina219;

    Wire.begin(SDA_Pin, SCL_Pin); // for I2C protocol

    // copied from example, will change later to better fit the needs of project 
    if (!ina219.begin()) {
        Serial.println("Failed to find INA219 chip");
        while (1) { delay(10); }
    }
    Serial.println("Measuring voltage and current with IN219...");
    
    // place holder once proper error handling in implemented 
    return 1; 
}

int take_measurment(void){
    
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadvoltage = busvoltage + (shuntvoltage / 1000);

    Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
    Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
    Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
    Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
    Serial.println("");

}   
