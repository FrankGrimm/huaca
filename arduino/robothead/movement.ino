#include <Servo.h>
Servo servos[SERVO_COUNT];

boolean reported_target_reached = false;
int servo_pins[SERVO_COUNT] = {5, 6};
int servo_current[SERVO_COUNT] = {-1, -1};
int servo_targets[SERVO_COUNT] = {-1, -1};
int servo_min[SERVO_COUNT] = {20, 20};
int servo_max[SERVO_COUNT] = {165, 165};
int servo_initial[SERVO_COUNT] = {80, 125};

void servo_set_initial(int servoIdx) {
  servo_targets[servoIdx] = servo_initial[servoIdx];
}

void servo_setup() {
  for(int servoIdx = 0; servoIdx < SERVO_COUNT; servoIdx++) {
    // initialize servo
    servos[servoIdx].attach(servo_pins[servoIdx]);
    servo_set_initial(servoIdx);
    servo_set(servoIdx, servo_targets[servoIdx]);
    delay(1);
    servo_current[servoIdx] = servos[servoIdx].read();
  }
}

void servo_set(int servoIdx, int pos) {
  servos[servoIdx].write(constrain(pos, servo_min[servoIdx], servo_max[servoIdx]));
}

void servo_set_target(int servoIdx, int target) {
  servo_targets[servoIdx] = constrain(target, servo_min[servoIdx], servo_max[servoIdx]);
  reported_target_reached = false;
}

void servo_read() {
  for(int servoIdx = 0; servoIdx < SERVO_COUNT; servoIdx++) {
    servo_current[servoIdx] = servos[servoIdx].read();
    delayMicroseconds(5);
  }
}

boolean servo_move() {
  boolean moved = false;
  
  for(int servoIdx = 0; servoIdx < SERVO_COUNT; servoIdx++) {
    if (servo_targets[servoIdx] > -1) {
      int servoSgn = servo_current[servoIdx] - servo_targets[servoIdx] < 0 ? -1 : 1;
      int servoAbs = abs(servo_current[servoIdx] - servo_targets[servoIdx]);

      if (servoAbs <= 2) {
        servo_set(servoIdx, servo_targets[servoIdx]);
        servo_targets[servoIdx] = -1;
      } else {
        servo_current[servoIdx] -= servoSgn;
        servo_set(servoIdx, servo_current[servoIdx]);
      }
      moved = true;
    }
  }
  
  if (!moved && !reported_target_reached) {
    Serial.println("{\"motorEvent\": \"targetReached\"}");
    reported_target_reached = true;
  }
  
  return moved;
}

void servo_report() {
  Serial.print("{\"servos\":{");
  for (int servoIdx = 0; servoIdx < SERVO_COUNT; servoIdx++) {
    Serial.print("\"servo");
    Serial.print(servoIdx, DEC);
    Serial.print("\": {\"position\": ");
    int servoPos = servos[servoIdx].read();
    Serial.print(servoPos, DEC);
    servo_current[servoIdx] = servoPos;
    Serial.print(", \"min\": ");
    Serial.print(servo_min[servoIdx], DEC);
    Serial.print(", \"max\": ");
    Serial.print(servo_max[servoIdx], DEC);
    if (servoIdx < SERVO_COUNT - 1) {
      Serial.print("}, ");
    } else {
      Serial.print("}");
      delayMicroseconds(10); // delay between servo reads
    }
  }
  Serial.println("} }");
}

