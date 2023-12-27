#include <AFMotor.h>
#include <SoftwareSerial.h>   
#include <Servo.h>              // Add library
Servo name_servo;    
Servo axle_servo; // New servo for the axle
SoftwareSerial Serial1(A1, A3); 

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 


int dist;                     
int strength;                
int check;                    
int i;
int uart[9];                   
const int HEADER = 0x59;      

void setup()
{

  name_servo.attach (9);  
  axle_servo.attach(10); // Attach the axle servo to slot 10

  Serial.begin(9600);         
  Serial1.begin(115200);     

  motor1.setSpeed(200);    
  motor2.setSpeed(200);    
   

}

void loop() {

 

  if (Serial1.available())               
  {
    if (Serial1.read() == HEADER)        
    {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER)      
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         
        {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))       
          dist = uart[2] + uart[3] * 256;     
          strength = uart[4] + uart[5] * 256; 

            Serial.println(dist);

            if(dist < 10) {
            
            axle_servo.write(45); // Turn the axle servo slightly left
          
          }

          if(dist < 5) {
            motor1.run(RELEASE); // Stop the motors
            motor2.run(RELEASE);
            
            name_servo.write(90); // Turn the lidar servo 90 degrees left
          } else {
            motor1.run(FORWARD); // Move the motors forward
            motor2.run(FORWARD);
            name_servo.write(0); // Turn the lidar servo back to the center
            axle_servo.write(0); // Turn the axle servo back to the center
          }
        }
      }
    }
  }

