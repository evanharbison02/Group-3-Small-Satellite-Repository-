#include "include/Comhand.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

//this is a test to chack for the repo
void handle_commhand(int input) {
   
    switch (input) {
        case 0: // Run X CC
            //setTorque(0, 0);
            Serial.println("DEBUG: Comhand read X");
            break;

        case 1: // Run Y CW
            //setTorque(0, 1);
            Serial.println("DEBUG: Comhand read Y");
            break;

        case 2: // Run Z CC
            //setTorque(1, 0);
            Serial.println("DEBUG: Comhand read Z");
            break;

        case 3: // Run Core1 CW
            //setTorque(1, 1);
            Serial.println("DEBUG: Commhand read Stop");
            break;
        case 4:
            Serial.println("DEBUG: Commhand read Stop all");
            break;
        default:  Serial.println("fall though switch statment");
    }
}

// no radio: inpu, parse, and handling 
void loop() {
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
/*
// mapped out for radio communiction 
void loop() {
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
/*
void loop() {
  
  take_measurment(1);

  float soc = get_curr_SoC();

  Serial.print("Current SoC: ");
  Serial.print(soc * 100, 1);
  Serial.println(" %");

  delay(2000);
}
*/