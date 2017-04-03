// ----------------------------------------
// SERVO

void servoMove(int tpos) {
  int d = tpos - servo_position;

  for (int i = 0; servo_position != tpos; i++) {
    servo_position += (d > 0) ? 1 : -1;
    servoPen.write(servo_position);
    delay(15);
  }
}

// ----------------------------------------
// SERVO SLEEP

int sleep_timer = 0;
boolean isAsleep = false;

void sleep() {
  if (!isAsleep) {
    sleep_timer++;
    delay(100);
    if (sleep_timer > MS_BEFORE_SERVO_SLEEP / 100) {
      isAsleep = true;
      servoPen.detach();
    }
  }
}

void wakeUp() {
  if (isAsleep) {
    sleep_timer = 0;
    isAsleep = false;
    servoPen.attach(servopin);
  }
}
