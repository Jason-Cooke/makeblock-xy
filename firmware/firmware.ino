// based on https://github.com/fogleman/xy/tree/master/firmware

#include "MeOrion.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>

// data stored in eeprom
static union{
    struct{
      char name[8];
      unsigned char motoADir;
      unsigned char motoBDir;
      unsigned char motorSwitch;
      int height;
      int width;
      int speed;
      int penUpPos;
      int penDownPos;
    }data;
    char buf[64];
}roboSetup;

int stepAuxDelay = 0;

// CONSTANTS
#define REQ_NEXT_CMD_CHAR 'N'
#define MS_BEFORE_SERVO_SLEEP 1000
#define SPEED_STEP 1
#define WIDTH 310
#define HEIGHT 380
#define STEPS_PER_MM 87.58 // the same as 3d printer
#define MIN_STEP_DELAY 250
#define MAX_STEP_DELAY 1000

// MOTORS
int motor1_dir_pin = mePort[PORT_1].s1; // PORT1 SLOT1
int motor1_step_pin = mePort[PORT_1].s2; // PORT1 SLOT2
int motor2_dir_pin = mePort[PORT_2].s1;
int motor2_step_pin = mePort[PORT_2].s2;

int stepdelay_min;
int stepdelay_max;

// motor directions
bool motorAfw = 1;
bool motorAbk = 0;
bool motorBfw = 0;
bool motorBbk = 1;

// LIMIT SWITCHES
int xlimit_pin1 = mePort[PORT_6].s1;
int xlimit_pin2 = mePort[PORT_6].s2;
int ylimit_pin1 = mePort[PORT_3].s1;
int ylimit_pin2 = mePort[PORT_3].s2;

bool y_limit_1_state = LOW;
bool y_limit_2_state = LOW;
bool x_limit_1_state = LOW;
bool x_limit_2_state = LOW;

// SERVO
int servopin = mePort[PORT_7].s2;
Servo servoPen;
int servo_position = 0;

float curX, curY, curZ;
float tarX, tarY, tarZ; // target xyz position
int tarA, tarB, posA, posB; // target stepper position

// ----------------------------------------
// ARDUINO

char buf[64];
int8_t bufindex;

void setup() {
  
  // set motors
  pinMode(motor1_step_pin, OUTPUT);
  pinMode(motor2_step_pin, OUTPUT);
  pinMode(motor1_dir_pin, OUTPUT);
  pinMode(motor2_dir_pin, OUTPUT);
  // set switches
  pinMode(ylimit_pin1, INPUT_PULLUP);
  pinMode(ylimit_pin2, INPUT_PULLUP);
  pinMode(xlimit_pin1, INPUT_PULLUP);
  pinMode(xlimit_pin2, INPUT_PULLUP);
  
  Serial.begin(115200);

  initRobotSetup();
  initPosition();
  
  // init servo
  servoPen.attach(servopin);
  delay(100);
  servoPen.write(servo_position);
  delay(1000);

  echoLimitSwitchesStates();
  delay(2000);

  goHome();

  requestNextCommand();
  
  Serial.println("Starting loop");
}

void loop() {

  if (Serial.available()) {
    wakeUp();

    char c = Serial.read();
    buf[bufindex++] = c;
    if (c == '\n') {
      buf[bufindex] = '\0';
      parseCmd(buf);
      memset(buf, 0, 64);
      bufindex = 0;
    }
    if(bufindex >= 64) bufindex=0;
    

  } else sleep();
  
}
