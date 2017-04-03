// ----------------------------------------
// PARSING

void parseCoordinate(char * cmd) {
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  tarX = curX;
  tarY = curY;
  while (str!=NULL) {
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'X') tarX = atof(str + 1);
    else if (str[0] == 'Y') tarY = atof(str + 1);
    else if (str[0] == 'Z') tarZ = atof(str + 1);
    else if (str[0] == 'A') stepAuxDelay = atoi(str + 1);
  }
  prepareMove();
}

void parseRobotSetup(char * cmd) {
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  while(str!=NULL){
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'A') roboSetup.data.motoADir = atoi(str + 1);
    else if (str[0] == 'B') roboSetup.data.motoBDir = atoi(str + 1);
    else if (str[0] == 'H') roboSetup.data.height = atoi(str + 1);
    else if (str[0] == 'W') roboSetup.data.width = atoi(str + 1);
    else if (str[0] == 'S') roboSetup.data.speed = atoi(str + 1);
  }
  syncRobotSetup();
}

void parseAuxDelay(char * cmd) {
  char * tmp;
  strtok_r(cmd, " ", &tmp);
  stepAuxDelay = atoi(tmp);
}

void parsePen(char * cmd) {
  char * tmp;
  strtok_r(cmd, " ", &tmp);
  int tpos = atoi(tmp);

  servoMove(tpos);
}

void parsePenPosSetup(char * cmd) {
  char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);
  while(str!=NULL){
    str = strtok_r(0, " ", &tmp);
    if (str[0] == 'U') roboSetup.data.penUpPos = atoi(str + 1);
    else if (str[0] == 'D') roboSetup.data.penDownPos = atoi(str + 1);
  }
  syncRobotSetup();
}

void parseSCode(char * cmd) {
  int code = atoi(cmd);
  switch(code){
    case 0:
      // reset to non-linear speed
      stepdelay_min = MIN_STEP_DELAY;
      stepdelay_max = MAX_STEP_DELAY;
      break;
    case 1:
      // set stepdelay value
      char * tmp;
      strtok_r(cmd, " ", &tmp);
      int value = atoi(tmp);
      stepdelay_min = value;
      stepdelay_max = value;
      break;
  }
}

void parseMcode(char * cmd) {
  int code = atoi(cmd);
  switch(code){
    case 1:   parsePen(cmd); break;
    case 2:   parsePenPosSetup(cmd); break;
    case 3:   parseAuxDelay(cmd); break;
    case 5:   parseRobotSetup(cmd); break;
    case 10:  echoRobotSetup(); break;
    case 11:  echoEndStop(); break;
  }
}

void parseGcode(char * cmd) {
  int code = atoi(cmd);
  switch(code){
    case 0:
    case 1: parseCoordinate(cmd); break;
    case 28: tarX=0; tarY=0; goHome(); break;
  }
}

void parseCmd(char * cmd) {
  requestNextCommand();
  if (cmd[0] == 'G') parseGcode(cmd + 1);
  else if (cmd[0] == 'M') parseMcode(cmd + 1);
  else if (cmd[0] == 'S') parseSCode(cmd + 1);
  else if (cmd[0] == 'P') echoPosition();
}

void requestNextCommand() {
  Serial.println(REQ_NEXT_CMD_CHAR);
}
