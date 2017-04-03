// ----------------------------------------
// XY MOVES

void stepperMoveA(int dir) {

  // set direction
  digitalWrite(motor2_dir_pin, dir);
  // move one step
  digitalWrite(motor2_step_pin, HIGH);
  delayMicroseconds(800);
  digitalWrite(motor2_step_pin, LOW);
  delayMicroseconds(800);
}

void stepperMoveB(int dir) {
  // set direction
  digitalWrite(motor1_dir_pin, dir);
  // move one step
  digitalWrite(motor1_step_pin, HIGH);
  delayMicroseconds(800);
  digitalWrite(motor1_step_pin, LOW);
  delayMicroseconds(800);
}

void doMove() {
  int mDelay = stepdelay_max;
  int speedDiff = -SPEED_STEP;
  int dA, dB, maxD;
  float stepA, stepB, cntA = 0, cntB = 0;
  int d;
  dA = tarA - posA;
  dB = tarB - posB;
  maxD = max(abs(dA), abs(dB));
  stepA = (float) abs(dA) / (float)maxD;
  stepB = (float) abs(dB) / (float)maxD;
  for (int i = 0; (posA != tarA) || (posB != tarB); i++) {
    // move A
    if (posA != tarA) {
      cntA += stepA;
      if (cntA >= 1) {
        d = dA > 0 ? motorAfw : motorAbk;
        posA += (dA > 0 ? 1 : -1);
        // don't move passed limit !
        if ((d > 0 && digitalRead(xlimit_pin2) == 1) || (d < 0 && digitalRead(xlimit_pin1) == 1)) stepperMoveA(d);
        cntA -= 1;
      }
    }
    // move B
    if (posB != tarB) {
      cntB += stepB;
      if (cntB >= 1) {
        d = dB > 0 ? motorBfw : motorBbk;
        posB += (dB > 0 ? 1 : -1);
        // don't move passed limit !
        if ((d > 0 && digitalRead(ylimit_pin2) == 1) || (d < 0 && digitalRead(ylimit_pin1) == 1)) stepperMoveB(d);
        cntB -= 1;
      }
    }
    mDelay = constrain(mDelay + speedDiff, stepdelay_min, stepdelay_max) + stepAuxDelay;
    delayMicroseconds(mDelay);
    if ((maxD - i) < ((stepdelay_max - stepdelay_min) / SPEED_STEP)) speedDiff = SPEED_STEP;
  }
  posA = tarA;
  posB = tarB;
}

void prepareMove() {
  float dx = tarX - curX;
  float dy = tarY - curY;
  float distance = sqrt(dx * dx + dy * dy);
  if (distance < 0.001) return;
  tarA = tarX * STEPS_PER_MM;
  tarB = tarY * STEPS_PER_MM;
  doMove();
  curX = tarX;
  curY = tarY;
}

void goHome() {

  // move to 0 position on x axis
  // so, move untill we trigger the limit switch x2
  // (makeblock manual calls it limit switch 3)
  while(digitalRead(xlimit_pin2) != 0) {
    stepperMoveA(motorAbk);
    delayMicroseconds(stepdelay_min);
  }
  
  // then we move the y axis untill limit switch y2
  // (makeblock manual calls it limit switch 2)
  while(digitalRead(ylimit_pin2) != 0) {
    stepperMoveB(motorBbk);
    delayMicroseconds(stepdelay_min);
  }

  /* OLD CODE
  // stop on either endstop touches
  while (digitalRead(xlimit_pin2) != 0 || digitalRead(ylimit_pin2) != 0) {
    if (digitalRead(xlimit_pin2) != 0) stepperMoveA(motorAbk);
    if (digitalRead(ylimit_pin2) != 0) stepperMoveB(motorBbk);
    delayMicroseconds(stepdelay_min);
  }
  */
  initPosition();
}

void initPosition() { curX = 0; curY = 0; posA = 0; posB = 0; }

