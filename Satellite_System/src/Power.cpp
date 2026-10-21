#include "include/Power.h"
#include <string.h>
#include <stdlib.h>

/*
    The last know State of Charge for the Satellite and Current Battry Capacity 
    May later use a log file to hold the last know SoC - Evan 
*/ 
// max battary cap is 10200 mAh
float SoC = 1.00;
float q_capacity = 0;
float q_max = 10200.00;
unsigned long last_time = 0;


// initialize the reading variables are globe 
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;

int set_up_INA219( void ){
    
    Wire.begin(SDA_Pin, SCL_Pin); // for I2C protocol

    q_capacity = q_max; 
    // this will be used for Sprint 1 till i can work out interrupts for the satallite 
    last_time = millis();

    // copied from example, will change later to better fit the needs of project 
    if (!ina219.begin()) {
        Serial.println("Failed to find INA219 chip");
        while (1) { delay(10); }
    }
    Serial.println("Measuring voltage and current with IN219...");
    
    // place holder once proper error handling in implemented 
    return 1; 
}

void take_measurment( int flag ){
    
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadvoltage = busvoltage + (shuntvoltage / 1000);
    
    // use a int flag to tell function to print out the readings 
    // this is usefull if interrupts are implemented, will crash if in interrupt and there is a Serial print  
    if ( flag == 1){
        Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
        Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
        Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
        Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
        Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
        Serial.println("");
    }


}   

float get_curr_SoC( void ){

    // take new reading to update values 
    take_measurment(0);
    
    // may not be needed, but what to leave it so that I can save the og current_mA value 
    float i = current_mA;
    
    unsigned long now = millis();
    unsigned long DT_S = now - last_time;
    last_time = now; 
    
    // need rework 
    SoC = SoC - (i * DT_S) / q_capacity;

    // will allow the SoC value to returned within 1.0 and 0.0 
    if( SoC > 1.0 ) return SoC = 1.0;
    else if( SoC < 0.0) return SoC = 0.0;
    else return Soc;

}