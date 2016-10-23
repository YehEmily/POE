#include <Servo.h>

/****************************************************
 * SERVOS
 ****************************************************/
Servo whale;          // creates a servo object to control the servo named whale
Servo swordfish;      // creates a servo object to control the servo named swordfish
  
/****************************************************
 * INSTANCE VARIABLES
 ****************************************************/

int pos = 0;            // variable to store the servo position
int sensorValue = 0;    // value read from sensor
int outputValue = 0;    // value output from sensor
int sensorMin = 1023;   // minimum sensor value
int sensorMax = 0;      // maximum sensor value

const int analogInPin = A0;         // analog input that sensor is attached to
const int whalePin = 9;             // analog output that whale is attached to
const int swordfishPin = 10;        // analog output that swordfish is attached to

/****************************************************
 * SET UP METHOD
 ****************************************************/

void setup() {
  whale.attach(whalePin);           // attaches servo whale to pin 9
  swordfish.attach(swordfishPin);   // attaches servo swordfish to pin 10
  
  Serial.begin(57600);              // begin communication between arduino and computer
}

/****************************************************
 * MAIN LOOP METHOD
 ****************************************************/

void loop() {
  Serial.println("begin");          // to mark the beginning of a loop
  
  for (pos = 90; pos >= 20; pos -= 5) {
         swordfish.write(pos);      // rotate swordfish servo
    for (int i = 180; i >= 50; i --) {
      whale.write(i);               // rotate whale servo
      sensorValue = analogRead(analogInPin);
     
      Serial.println(sensorValue);
      Serial.println(pos);
      Serial.println(i);
      delay(15); // slow down because our mechanism was rotating like lightning
    }
  }
}
