#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <ctype.h>

SoftwareSerial ble(50, 51); // RX, TX
AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
int speed=255;


void backw(){
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}
void forw(){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}
void right(){
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
}
void left(){
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
}
void forwleft(){
    motor1.setSpeed(speed/2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.setSpeed(speed/2);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}
void forwright(){
    motor1.run(FORWARD);
    motor2.setSpeed(speed/2);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.setSpeed(speed/2);
    motor4.run(FORWARD);
}
void stopAll(){
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void Gomotor1(){
    motor1.run(FORWARD);
}

void Gomotor2(){
    motor2.run(FORWARD);
}

void Gomotor3(){
    motor3.run(FORWARD);
}

void Gomotor4(){
    motor4.run(FORWARD);
}
void inscease10(int x){
  speed = int(speed*1.1);
  motor1.setSpeed(speed);     // set the speed to 200/255
  motor2.setSpeed(speed);     // set the speed to 200/255
  motor3.setSpeed(speed);     // set the speed to 200/255
  motor4.setSpeed(speed);     // set the speed to 200/255
}

void decrease10(int x){
  speed = int(speed*0.9);
  motor1.setSpeed(speed);     // set the speed to 200/255
  motor2.setSpeed(speed);     // set the speed to 200/255
  motor3.setSpeed(speed);     // set the speed to 200/255
  motor4.setSpeed(speed);     // set the speed to 200/255
}


void setAllSpeed(int x){
  if(x == 0) x = 5;
  speed = x*25;
  motor1.setSpeed(speed);     // set the speed to 200/255
  motor2.setSpeed(speed);     // set the speed to 200/255
  motor3.setSpeed(speed);     // set the speed to 200/255
  motor4.setSpeed(speed);     // set the speed to 200/255
}
void setup() {
  setAllSpeed(10);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
}
char  val;
void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    Serial.print(val);
  }
  switch (val){
    case 'F':
      forw();
      break;
    case 'B':
      backw();
      break;
    case 'R':
      right();
      break;
    case 'L':
      left();
      break;
    case 'q':
      setAllSpeed(10);
      break;
    case '1':
      Gomotor1();
      break;
    case '2':
      Gomotor2();
      break;
    case '3':
      Gomotor3();
      break;
    case '4':
      Gomotor4();
      break;
    case 'S':
      stopAll();
      break;
    default:
      if(isDigit(val)){
        setAllSpeed(val);
        Serial.print(val);
      }
      break;
  }
}
