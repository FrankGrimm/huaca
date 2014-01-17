#define BUMP_COUNT 3
const byte bumperPins[] = {11, 12, 13};
boolean bumperValues[] = {false, false, false};
/*
D11 Bumper Front right
D12 Bumper Front center
D13 Bumper Front left
*/

void bumpers_setup() {
  for (int bumperIdx = 0; bumperIdx < BUMP_COUNT; bumperIdx++) {
    pinMode(bumperPins[bumperIdx], INPUT);
  }
}

boolean bumper_hit() {
  for (int bumperIdx = 0; bumperIdx < BUMP_COUNT; bumperIdx++) {
    if (bumperValues[bumperIdx]) return true;
  }
  
  return false;
}

void bumpers_read_all(void) {
  for (int bumperIdx = 0; bumperIdx < BUMP_COUNT; bumperIdx++) {
    int bumperState = digitalRead(bumperPins[bumperIdx]);
    bumperValues[bumperIdx] = (bumperState == LOW);
  }
}

void serial_output_bumpers() {
  Serial.print("{\"bumpers\": ");
  Serial.print(BUMP_COUNT, DEC);
  Serial.print(", \"states\": [");
  for (int bumpIdx = 0; bumpIdx < BUMP_COUNT; bumpIdx++) {
    if (bumperValues[bumpIdx]) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    if (bumpIdx < (BUMP_COUNT - 1)) {
      Serial.print(", ");
    }
  }
  Serial.println("]}");
}
