int rgb_pins[3] = {9, 11, 10};
// red, green, blue
// (common anode RGB led)

void rgb_test() {
  rgb_set(255, 0, 0);  // red
  delay(400);
  rgb_set(0, 255, 0);  // green
  delay(400);
  rgb_set(0, 0, 255);  // blue
  delay(400);
  rgb_set(255, 255, 0);  // yellow
  delay(400);  
  rgb_set(80, 0, 80);  // purple
  delay(400);
  rgb_set(0, 255, 255);  // aqua
  delay(400);
  rgb_off();
}

void rgb_setup() {
  for (int idx = 0; idx < 3; idx++) {
    pinMode(rgb_pins[idx], OUTPUT);
  }
  rgb_test();
}
 
void rgb_set(int red, int green, int blue) {
  analogWrite(rgb_pins[0], 255 - red);
  analogWrite(rgb_pins[1], 255 - green);
  analogWrite(rgb_pins[2], 255 - blue);
  
  Serial.print("{\"rgb\": [");
  Serial.print(red, DEC);
  Serial.print(", ");
  Serial.print(green, DEC);
  Serial.print(", ");
  Serial.print(blue, DEC);
  Serial.println("]}");
}

void rgb_off() {
  rgb_set(0, 0, 0);
}

void rgb_setcode(int target) {
  switch(target) {
    case 0:
    rgb_off();
    break;
    case 1:
    rgb_set(255, 0, 0);  // red
    break;
    case 2:
    rgb_set(0, 255, 0);  // green
    break;
    case 3:
    rgb_set(0, 0, 255);  // blue
    break;
    case 4:
    rgb_set(255, 255, 0);  // yellow
    break;
    case 5:
    rgb_set(80, 0, 80);  // purple
    break;
    case 6:
    rgb_set(0, 255, 255);  // aqua
    break;
    case 7:
    break;
    case 8:
    break;
    case 9:
    break;
  }
}
