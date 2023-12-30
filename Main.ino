#include <AFMotor.h>
#include <SoftwareSerial.h>   //header file of software serial port
SoftwareSerial Serial1(A1, A3); 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>//define software serial port name as Serial1 and define pin2 as RX & pin3 as TX

LiquidCrystal_I2C lcd(0x20, 16, 2);

AF_DCMotor motor1(1); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4); // create motor #4, 64KHz pwm

int dist;                     //actual distance measurements of LiDAR
int strength;                 //signal strength of LiDAR
int check;                    //save check value
int i;
int uart[9];                   //save data measured by LiDAR
const int HEADER = 0x59;      //frame header of data package

void setup()
{
  Serial.begin(9600);         //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);      //set bit rate of serial port connecting LiDAR with Arduino

  motor1.setSpeed(255);     // set the speed to 200/255
  motor2.setSpeed(255);     // set the speed to 255/255
  motor3.setSpeed(255);     // set the speed to 255/255
  motor4.setSpeed(255);     // set the speed to 200/255
	lcd.begin();
}

void loop() {
  if (Serial1.available())                //check if serial port has data input
  {
    if (Serial1.read() == HEADER)        //assess data package frame header 0x59
    {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER)      //assess data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         //save data in array
        {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))        //verify the received data as per protocol
        {
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
 motor1.run(FORWARD);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(FORWARD);
            lcd.backlight();
 lcd.clear();  // Clear the LCD screen
        lcd.print(dist);
Serial.println(dist);

          if(dist < 30) {
            name_servo.write(180);
            int leftDist;
            int rightDist;
            rightDist = dist;
            if(rightDist < 15){
              motor1.run(FORWARD);
              motor2.run(BACKWARD);
              motor3.run(BACKWARD);
              motor4.run(FORWARD);
            }
           //  delay(100);
          } else {
            motor1.run(FORWARD);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(FORWARD);
          }
          
        }
      }
    }
  }
}
