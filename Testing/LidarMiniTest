#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>  // Add library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

Servo name_servo;
SoftwareSerial Serial1(A1, A3);

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int dist;
int strength;
int check;
int i;
int uart[9];
const int HEADER = 0x59;

void setup() {

  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();

  name_servo.attach(10);

  Serial.begin(9600);
  Serial1.begin(115200);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
}

void loop() {

  if (Serial1.available()) {
    if (Serial1.read() == HEADER) {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))
          dist = uart[2] + uart[3] * 256;
        strength = uart[4] + uart[5] * 256;

        Serial.println(dist);
        lcd.clear();  // Clear the LCD screen
        lcd.print("Distance: " + String(dist));

        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);

        if (dist < 5) {
          motor1.run(FORWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(FORWARD);
          lcd.print("         Turning Right");

          name_servo.write(90);

        } else {
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          lcd.print("        Going Forward");
        }
      }
    }
  }
}
