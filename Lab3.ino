#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

/***************************************************
 * Instance variables 
 ***************************************************/
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftWheel = AFMS.getMotor(3);
Adafruit_DCMotor *rightWheel = AFMS.getMotor(4);

const int sensor_1 = A0;  // Analog input that sensor is attached to
const int sensor_2 = A1;

int sensorValue_1 = 0;  // Values read from sensor
int sensorValue_2 = 0;

String input;           // Stores user input
int threshold = 700;    // Threshold value (for changing sensors' sensitivity from user input)
float factor = 1;       // Speed factor (for changing speed from user input)
unsigned long time_elapsed;
unsigned long total_time_elapsed;

/***************************************************
 * Setup function
 ***************************************************/
void setup() {
  Serial.begin(1200);
  AFMS.begin();
  time_elapsed = 0;
  total_time_elapsed = 0;

  // Prompt user for input
  Serial.println("Enter a threshold value for the IR sensors, then a speed factor for the motors.");
  Serial.println("Format: THRESHOLD,FACTOR");
  Serial.println("Example: 700,2");
}

/***************************************************
 * Loop function
 ***************************************************/
void loop() {
  time_elapsed = millis();
  
  if (Serial.available() > 0) { // Check if there's user input
    input = Serial.readString(); // Store the input
    threshold = input.substring(0, input.indexOf(',')).toInt(); // Capture substring up to comma as threshold
    factor = input.substring(input.indexOf(',')+1).toFloat(); // Capture substring after comma as factor
    // For debugging - tell us if values were detected and print the values
    Serial.println("New user input detected."); 
    Serial.print("\nThreshold: ");
    Serial.print(threshold);
    Serial.print("\nFactor: ");
    Serial.print(factor);
  }

  sensorValue_1 = analogRead(sensor_1); // Value read from sensor 1
  sensorValue_2 = analogRead(sensor_2); // Value read from sensor 2

  Serial.println(sensorValue_1);
  Serial.println(sensorValue_2);
  total_time_elapsed += time_elapsed;
  Serial.println(total_time_elapsed);

  leftWheel->run(BACKWARD);   // Run the wheels (backwards, because that's the way
  rightWheel->run(BACKWARD);  // we wanted to orient our chassis and motors (:

  leftWheel->setSpeed(factor*15);   // Set initial speed (speed motors go at when not "seeing" black tape)
  rightWheel->setSpeed(factor*15);

  while (sensorValue_1 >= threshold) {    // If "seeing" black tape over sensor 1, do this
    leftWheel->setSpeed(2.0*factor);
    rightWheel->setSpeed(25*factor);
    Serial.println(sensorValue_1);
    Serial.println(sensorValue_2);
    sensorValue_1 = analogRead(sensor_1); // Update the sensor reading
    total_time_elapsed += time_elapsed;
    Serial.println(total_time_elapsed);
  }
  while (sensorValue_2 >= threshold) {    // If "seeing" black tape over sensor 2, do this
    rightWheel->setSpeed(2*factor);
    leftWheel->setSpeed(25*factor);
    Serial.println(sensorValue_1);
    Serial.println(sensorValue_2);
    sensorValue_2 = analogRead(sensor_2); // Update the sensor reading
    total_time_elapsed += time_elapsed;
    Serial.println(total_time_elapsed);
  }
}
