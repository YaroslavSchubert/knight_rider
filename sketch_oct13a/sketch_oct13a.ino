#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <ctype.h>

SoftwareSerial ble(50, 51); // RX, TX
// AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
// AF_DCMotor motor2(2, MOTOR12_64KHZ);
// AF_DCMotor motor3(3, MOTOR34_64KHZ);
// AF_DCMotor motor4(4, MOTOR34_64KHZ);

AF_DCMotor motors[4] = {
                        // AF_DCMotor(1, MOTOR34_64KHZ),
                        // AF_DCMotor(2, MOTOR34_64KHZ),
                        // AF_DCMotor(3, MOTOR34_64KHZ),
                        // AF_DCMotor(4, MOTOR34_64KHZ)
                        AF_DCMotor(4, MOTOR34_64KHZ),
                        AF_DCMotor(3, MOTOR34_64KHZ),
                        AF_DCMotor(2, MOTOR34_64KHZ),
                        AF_DCMotor(1, MOTOR34_64KHZ)
};
float motor_correction[4] = {
                             1,
                             1,
                             1,
                             1 // 1.2
};
int motor_max_forward[4] = {
                            250,
                            250,
                            250,
                            250,
};
int motor_max_backward[4] = {
                             -250,
                             -250,
                             -250,
                             -250,
};
int states[4] = {
                 RELEASE,
                 RELEASE,
                 RELEASE,
                 RELEASE
};

// # define MAX_FORWARD 50
// # define MAX_BACKWARD -50

enum class Action {
                   Stop = 1,
                   MaxForward = 2,
                   MaxBackward = 3,
                   MaxHalfForward = 4,
                   MaxHalfBackward = 5
};

void setup_motors(){
  for (int i=0; i<4; ++i){
    motors[i].run(RELEASE);
    states[i] = RELEASE;
  }
}

// int speed=255;


// void backw(){
//   motor1.run(BACKWARD);
//   motor2.run(BACKWARD);
//   motor3.run(BACKWARD);
//   motor4.run(BACKWARD);
// }
// void forw(){
//   motor1.run(FORWARD);
//   motor2.run(FORWARD);
//   motor3.run(FORWARD);
//   motor4.run(FORWARD);
// }
// void right(){
//   motor1.run(BACKWARD);
//   motor2.run(FORWARD);
//   motor3.run(BACKWARD);
//   motor4.run(FORWARD);
// }
// void left(){
//   motor1.run(FORWARD);
//   motor2.run(BACKWARD);
//   motor3.run(FORWARD);
//   motor4.run(BACKWARD);
// }
// void forwleft(){
//   motor1.setSpeed(speed/2);
//   motor1.run(FORWARD);
//   motor2.run(FORWARD);
//   motor3.setSpeed(speed/2);
//   motor3.run(FORWARD);
//   motor4.run(FORWARD);
// }
// void forwright(){
//   motor1.run(FORWARD);
//   motor2.setSpeed(speed/2);
//   motor2.run(FORWARD);
//   motor3.run(FORWARD);
//   motor4.setSpeed(speed/2);
//   motor4.run(FORWARD);
// }
// void stopAll(){
//   motor1.run(RELEASE);
//   motor2.run(RELEASE);
//   motor3.run(RELEASE);
//   motor4.run(RELEASE);
// }

// void Gomotor1(){
//   motor1.run(FORWARD);
// }

// void Gomotor2(){
//   motor2.run(FORWARD);
// }

// void Gomotor3(){
//   motor3.run(FORWARD);
// }

// void Gomotor4(){
//   motor4.run(FORWARD);
// }
// void inscease10(int x){
//   speed = int(speed*1.1);
//   motor1.setSpeed(speed);     // set the speed to 200/255
//   motor2.setSpeed(speed);     // set the speed to 200/255
//   motor3.setSpeed(speed);     // set the speed to 200/255
//   motor4.setSpeed(speed);     // set the speed to 200/255
// }

// void decrease10(int x){
//   speed = int(speed*0.9);
//   motor1.setSpeed(speed);     // set the speed to 200/255
//   motor2.setSpeed(speed);     // set the speed to 200/255
//   motor3.setSpeed(speed);     // set the speed to 200/255
//   motor4.setSpeed(speed);     // set the speed to 200/255
// }

int selected_motor = 0; // 0 is all
int speeds[4] = {0,0,0,0};
bool g_engine_on = false;

// void setAllSpeed(int x){
//   if(x == 0) x = 5;
//   speed = x*25;
//   motor1.setSpeed(speed);     // set the speed to 200/255
//   motor2.setSpeed(speed);     // set the speed to 200/255
//   motor3.setSpeed(speed);     // set the speed to 200/255
//   motor4.setSpeed(speed);     // set the speed to 200/255
// }


// enum class Direction {
//                       Forward = 1,
//                       Backward = 2,
// };

void change_speed_motor(int motor_idx, int inc){
  int current = speeds[motor_idx];
  // int next = current + (int)round(motor_correction[motor_idx] * inc);
  int next = current + inc;
  // Serial.print("next: ");
  // Serial.print(next);

  int maxf = motor_max_forward[motor_idx];
  int maxb = motor_max_backward[motor_idx];
  if (next < 0 && next < maxb){
    next = maxb;
  }else if (next > 0 && next > maxf){
    next = maxf;
  }
  if (current >= 0 && next < 0){
    if (g_engine_on){
      motors[motor_idx].run(BACKWARD);
    }else{
      motors[motor_idx].run(RELEASE);
    }
    states[motor_idx] = BACKWARD;
  }else if (current <= 0 && next > 0){
    if (g_engine_on){
      motors[motor_idx].run(FORWARD);
    }else{
      motors[motor_idx].run(RELEASE);
    }
    states[motor_idx] = FORWARD;
  }else if (next == 0){
    motors[motor_idx].run(RELEASE);
    states[motor_idx] = RELEASE;
  }
  speeds[motor_idx] = next;
  if (next < 0){
    next = - next;
  }
  motors[motor_idx].setSpeed(next);
}

void change_speed(int inc){
  if (selected_motor == 0){
    for (int i=0; i<4; ++i){
      change_speed_motor(i, inc);
    }
  }else if (selected_motor == 5){ // left
    change_speed_motor(0, inc);
    change_speed_motor(2, inc);
  }else if (selected_motor == 6){
    change_speed_motor(1, inc);
    change_speed_motor(3, inc);
  }else{
    change_speed_motor(selected_motor - 1, inc);
  }
}

void set_speed_motor(int motor_idx, Action action){
  int current = speeds[motor_idx];
  bool change_speed = true;
  int inc = 0;

  int maxf = motor_max_forward[motor_idx];
  int maxb = motor_max_backward[motor_idx];
  switch(action){
  case Action::Stop:
    motors[motor_idx].run(RELEASE);
    states[motor_idx] = RELEASE;
    motors[motor_idx].setSpeed(0);
    speeds[motor_idx] = 0;
    change_speed = false;
    break;
  case Action::MaxForward:
    inc = maxf - current;
    break;
  case Action::MaxHalfForward:
    inc = (int)(maxf/2) - current;
    break;
  case Action::MaxBackward:
    inc = maxb - current;
    break;
  case Action::MaxHalfBackward:
    inc = (int)(maxb/2) - current;
    break;
  }

  if (change_speed){
    int next = current + inc;
    if (next < 0 && next < maxb){
      next = maxb;
    }else if (next > 0 && next > maxf){
      next = maxf;
    }
    if (current >= 0 && next < 0){
      if (g_engine_on){
        motors[motor_idx].run(BACKWARD);
      }else{
        motors[motor_idx].run(RELEASE);
      }
      states[motor_idx] = BACKWARD;
    }else if (current <= 0 && next > 0){
      if (g_engine_on){
        motors[motor_idx].run(FORWARD);
      }else{
        motors[motor_idx].run(RELEASE);
      }
      states[motor_idx] = FORWARD;
    }else if (next == 0){
      motors[motor_idx].run(RELEASE);
      states[motor_idx] = RELEASE;
    }
    speeds[motor_idx] = next;
    if (next < 0){
      next = - next;
    }
    motors[motor_idx].setSpeed(next);
  }
}

void set_speed(Action action){
  if (selected_motor == 0){
    for (int i=0; i<4; ++i){
      set_speed_motor(i, action);
    }
  }else if (selected_motor == 5){ // left
    set_speed_motor(0, action);
    set_speed_motor(2, action);
  }else if (selected_motor == 6){
    set_speed_motor(1, action);
    set_speed_motor(3, action);
  }else{
    set_speed_motor(selected_motor - 1, action);
  }
}

void stop(){
  set_speed(Action::Stop);
}
void forward(){
  change_speed(10);
}
void backward(){
  change_speed(-10);
}
void forwardMax(){
  set_speed(Action::MaxForward);
}
void backwardMax(){
  set_speed(Action::MaxBackward);
}

void right(){
  int prev_selected_motor = selected_motor;
  selected_motor = 0;
  set_speed(Action::MaxForward);
  selected_motor = 5; // left side
  set_speed(Action::MaxHalfBackward);
  // set_speed(Action::Stop);
  selected_motor = prev_selected_motor;
}
void left(){
  int prev_selected_motor = selected_motor;
  selected_motor = 0;
  set_speed(Action::MaxForward);
  selected_motor = 6; // right side
  set_speed(Action::MaxHalfBackward);
  // set_speed(Action::Stop);
  selected_motor = prev_selected_motor;
}
void rightMax(){
  int prev_selected_motor = selected_motor;
  selected_motor = 0;
  set_speed(Action::MaxForward);
  selected_motor = 5; // left side
  // set_speed(Action::MaxHalfBackward);
  set_speed(Action::MaxBackward);
  selected_motor = prev_selected_motor;
}
void leftMax(){
  int prev_selected_motor = selected_motor;
  selected_motor = 0;
  set_speed(Action::MaxForward);
  selected_motor = 6; // right side
  // set_speed(Action::MaxHalfBackward);
  set_speed(Action::MaxBackward);
  selected_motor = prev_selected_motor;
}

void save_max(){
  for (int i=0; i<4; ++i){
    motor_max_forward[i] = speeds[i];
    motor_max_backward[i] = - abs(speeds[i]);
  }
}
void reset_max(){
  for (int i=0; i<4; ++i){
    motor_max_forward[i] = 250;
    motor_max_backward[i] = -250;
  }
}

void engine(bool enabled){
  g_engine_on = enabled;
  if (g_engine_on){
    for (int i=0; i<4; ++i){
      motors[i].run(states[i]);
    }
  }else{
    for (int i=0; i<4; ++i){
      motors[i].run(RELEASE);
    }
  }
}

bool g_reset = true;

void reset(){
  // Serial.begin(9600);
  Serial.begin(9600);

  selected_motor = 0;
  set_speed(Action::Stop);
  g_reset = false;
  g_engine_on = false;
  Serial.println("reset_");
}

void setup() {
  // setAllSpeed(0);
  // Serial.println("Motor test!");
  reset();
}

void test(){
  motors[0].run(RELEASE);
  motors[1].run(RELEASE);
  motors[2].run(RELEASE);
  motors[3].run(RELEASE);
  motors[0].setSpeed(0);
  motors[1].setSpeed(0);
  motors[2].setSpeed(0);
  motors[3].setSpeed(0);
  delay(2000);

  motors[0].run(FORWARD);
  motors[0].setSpeed(100);
  delay(2000);
  motors[0].run(RELEASE);
  motors[0].setSpeed(0);

  motors[1].run(FORWARD);
  motors[1].setSpeed(100);
  delay(2000);
  motors[1].run(RELEASE);
  motors[1].setSpeed(0);

  motors[2].run(FORWARD);
  motors[2].setSpeed(100);
  delay(2000);
  motors[2].run(RELEASE);
  motors[2].setSpeed(0);

  motors[3].run(FORWARD);
  motors[3].setSpeed(100);
  delay(2000);
  motors[3].run(RELEASE);
  motors[3].setSpeed(0);
}

void loop_test() {
  if (g_reset){
    reset();
  }

  char cmd = '-';

  if (Serial.available() > 0) {
    cmd = Serial.read();
    Serial.print("received:");
    Serial.print(cmd);
    Serial.print("selected_motor:");
    Serial.print(selected_motor);
    Serial.print("speeds:");
    for (int i = 0; i<4; ++i){
      Serial.print(speeds[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

  selected_motor = 0;
  set_speed(Action::Stop);
  delay(2000);

  // test();
  selected_motor = 1;
  set_speed(Action::MaxForward);
  delay(2000);

  selected_motor = 1;
  set_speed(Action::Stop);
  delay(2000);

  selected_motor = 2;
  set_speed(Action::MaxForward);
  delay(2000);

  selected_motor = 2;
  set_speed(Action::Stop);
  delay(2000);

  selected_motor = 3;
  set_speed(Action::MaxForward);
  delay(2000);

  selected_motor = 3;
  set_speed(Action::Stop);
  delay(2000);

  selected_motor = 4;
  set_speed(Action::MaxForward);
  delay(2000);

  selected_motor = 4;
  set_speed(Action::Stop);
  delay(2000);

}

void loop() {
  if (g_reset){
    reset();
  }

  char cmd = '-'; // no action

  bool use_serial = false;
  if (Serial.available() > 0) {
    cmd = Serial.read();
    // Serial.print("received: ");
    // Serial.print(val);
    // Serial.println("_");
    use_serial = true;
  }


  switch(cmd){
  case '0':
    selected_motor = 0;
    break;
  case '1':
    selected_motor = 1;
    break;
  case '2':
    selected_motor = 2;
    break;
  case '3':
    selected_motor = 3;
    break;
  case '4':
    selected_motor = 4;
    break;
  case '5':
    selected_motor = 5;
    break;
  case '6':
    selected_motor = 6;
    break;
  case 's':
    stop();
    break;
  case 'f':
    forward();
    break;
  case 'b':
    backward();
    break;
  case 'S':
    stop();
    break;
  case 'u':
    save_max();
    break;
  case 'U':
    reset_max();
    break;
  case 'F':
    forwardMax();
    break;
  case 'B':
    backwardMax();
    break;
  case 'l':
    left();
    break;
  case 'L':
    leftMax();
    break;
  case 'r':
    right();
    break;
  case 'R':
    rightMax();
    break;
  case 'e':
    engine(true);
    break;
  case 'E':
    engine(false);
    break;
  }

  if (use_serial) {
    // Serial.write("r");
    // Serial.print("r");
    Serial.print("received: ");
    Serial.print(cmd);
    Serial.print(" selected_motor: ");
    Serial.print(selected_motor);
    Serial.print(" speeds: ");
    for (int i = 0; i<4; ++i){
      Serial.print(speeds[i]);
      Serial.print(" ");
    }
    // // Serial.println();
    Serial.println("_");
    Serial.flush();
  }

  cmd = '-'; // no action

  // case 'F':
  //   forward();
  //   selected_motor = 4;
  //   break;
  // }

  // switch (val){
  // case '0':
  //   selected_motor = 0;
  //   break;
  // case 'F':
  //   forw();
  //   break;
  // case 'B':
  //   backw();
  //   break;
  // case 'R':
  //   right();
  //   break;
  // case 'L':
  //   left();
  //   break;
  // case 'q':
  //   setAllSpeed(10);
  //   break;
  // case '1':
  //   Gomotor1();
  //   break;
  // case '2':
  //   Gomotor2();
  //   break;
  // case '3':
  //   Gomotor3();
  //   break;
  // case '4':
  //   Gomotor4();
  //   break;
  // case 'S':
  //   stopAll();
  //   break;
  // default:
  //   if(isDigit(val)){
  //     setAllSpeed(val);
  //     Serial.print(val);
  //   }
  //   break;
  // }
}
