#include "include/Power.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if( set_up_INA219() == 0 ){
    return;
  }


}

void loop() {
  
  take_measurment(1);

  float soc = get_curr_SoC();

  Serial.print("Current SoC: ");
  Serial.print(soc * 100, 1);
  Serial.println(" %");

  delay(2000);
}
