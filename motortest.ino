#include <AFMotor.h>


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


void setup() {
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
}


void loop() {
  // All motors spin forward for 2 seconds
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);


  // Third motor stops, robot rotates 90 degrees
  motor3.run(RELEASE);
   
 
  // Assuming it takes 1 second to rotate 90 degrees
  delay(8000);


  // All motors spin forward again
 
}



