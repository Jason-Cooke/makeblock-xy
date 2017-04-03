// ----------------------------------------
// ECHO

// print the states of the switch limits
void echoLimitSwitchesStates(){

  Serial.println("Switch limits");
  Serial.print("x1:");
  Serial.println(digitalRead(xlimit_pin1));
  Serial.print("x2:");
  Serial.println(digitalRead(xlimit_pin2));
  Serial.print("y1:");
  Serial.println(digitalRead(ylimit_pin1));
  Serial.print("y2:");
  Serial.println(digitalRead(ylimit_pin2));
}

// print the value of motor directions
void echoMotorsDirections(){
  Serial.println("Motor directions:");
  Serial.print("motorAfw:");
  Serial.println(motorAfw);
  Serial.print("motorAbk:");
  Serial.println(motorAbk);
  Serial.print("motorBfw:");
  Serial.println(motorBfw);
  Serial.print("motorBBk:");
  Serial.println(motorBbk);
}

// print the position
void echoPosition() {
  Serial.print("POS X");
  Serial.print(curX);
  Serial.print(" Y");
  Serial.println(curY);
}

void echoRobotSetup() {
  Serial.print("M10 XY ");
  Serial.print(roboSetup.data.width); Serial.print(' ');
  Serial.print(roboSetup.data.height); Serial.print(' ');
  Serial.print(curX); Serial.print(' ');
  Serial.print(curY); Serial.print(' ');
  Serial.print("A"); Serial.print((int)roboSetup.data.motoADir);
  Serial.print(" B"); Serial.print((int)roboSetup.data.motoBDir);
  Serial.print(" H"); Serial.print((int)roboSetup.data.motorSwitch);
  Serial.print(" S"); Serial.print((int)roboSetup.data.speed);
  Serial.print(" U"); Serial.print((int)roboSetup.data.penUpPos);
  Serial.print(" D"); Serial.println((int)roboSetup.data.penDownPos);
}

void echoEndStop() {
  Serial.print("M11 ");
  Serial.print(digitalRead(xlimit_pin1)); Serial.print(" ");
  Serial.print(digitalRead(xlimit_pin2)); Serial.print(" ");
  Serial.print(digitalRead(ylimit_pin1)); Serial.print(" ");
  Serial.println(digitalRead(ylimit_pin2));
}
