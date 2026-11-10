#include "include/Attitude.h" 

const char* axis_of_three[]{
    "X",
    "Y",
    "Z"
};

int run_wheel_mock(int axis, direction dir){
    Serial.print("running: ");
    Serial.print(axis_of_three[axis - 2]);

    if(dir == CC){
        Serial.print(" ");
        Serial.println("CC");
    }else{
        Serial.print(" ");
        Serial.println("CW");
    }
    return axis - 2; // this is the int value that will be used with the leds and map to 

}

int stop_mock(int axis){
    Serial.print("stopping: ");
    Serial.println(axis_of_three[axis - 2]);
    return 3; //place holder till i get to the lab
}

int stop_all_mock(){
    Serial.print("stopping all");
    return 4;
}
