// ----------------------------------------
// LOCAL DATA

void initRobotSetup() {
  for(int i = 0; i < 64; i++) roboSetup.buf[i] = EEPROM.read(i);

  if (strncmp(roboSetup.data.name,"XY4", 3) != 0) {
    Serial.println("set to default setup");
    // set to default setup
    memset(roboSetup.buf, 0, 64);
    memcpy(roboSetup.data.name, "XY4", 3);
    roboSetup.data.motoADir = 0;
    roboSetup.data.motoBDir = 0;
    roboSetup.data.width = WIDTH;
    roboSetup.data.height = HEIGHT;
    roboSetup.data.motorSwitch = 0;
    roboSetup.data.speed = 100;
    roboSetup.data.penUpPos = 160;
    roboSetup.data.penDownPos = 90;
    syncRobotSetup();
  }

  /* OLD CODE
   * now motor directions are defined before setup
  // init motor direction
  // yzj, match to standard connection of xy
  // A = x, B = y
  if (roboSetup.data.motoADir == 0) {
    motorAfw = -1;
    motorAbk = 1;
  } else {
    motorAfw = 1;
    motorAbk = -1;
  }
  if (roboSetup.data.motoBDir == 0) {
    motorBfw = -1;
    motorBbk = 1;
  } else {
    motorBfw = 1;
    motorBbk = -1;
  }
  */

  // why this is used?
  // why not just usign the const var?
  stepdelay_min = MIN_STEP_DELAY;
  stepdelay_max = MAX_STEP_DELAY;
}

void syncRobotSetup() {
  for (int i = 0; i < 64; i++) EEPROM.write(i, roboSetup.buf[i]);
}
