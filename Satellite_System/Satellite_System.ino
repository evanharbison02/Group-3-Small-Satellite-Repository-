#include "include/Power.h"
#include <string.h>
#include <stdlib.h>

const float SoC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if( set_up_INA219 == 0 ){
    return;
  }


}

void loop() {

  take_measurment(1);

  SoC = get_curr_SoC();

  Serial.print("Current SoC: ");
  Serial.print(SoC * 100, 1);
  Serial.println(" %");

  delay(2000);
}
