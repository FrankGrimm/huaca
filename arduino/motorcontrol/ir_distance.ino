#define IR_COUNT 4
const byte irPins[] = {A0, A2, A1, A3};
float irValues[] = {-1.0, -1.0, -1.0, -1.0};
/*
A0 IR Front right
A2 IR Front center
A1 IR Front left
A3 IR Back
*/

// http://www.arduino.cc/playground/Main/ReadGp2d12Range
// output: cm
float gp2d12_range(byte pin) {
  int tmp;
  tmp = analogRead(pin);
  if (tmp < 3)
    return -1; // invalid value
  return (6787.0 /((float)tmp - 3.0)) - 4.0;
}

void ir_read_all() {
  for(byte irIdx = 0; irIdx < IR_COUNT; irIdx++) {
    irValues[irIdx] = gp2d12_range(irPins[irIdx]);
    if (irValues[irIdx] < 0.0 || irValues[irIdx] > 800.0) {
      // error or out of valid zone
      irValues[irIdx] = -1.0;
    }
  }
}

boolean ir_tooclose_front() {
  boolean res = false;
  for (int irIdx = 0; irIdx <= 2; irIdx++) {
    if (irValues[irIdx] < 8.0 && irValues[irIdx] > 0.0) {
      res = true;
    }
  }
  return res;
}

boolean ir_tooclose_back() {
  return (irValues[3] < 10.0 && irValues[3] > 0.0);
}

/* IR follow logic */
boolean ir_inhitzone(byte idx) {
  return (irValues[idx] > 7 && irValues[idx] <  20);
}

byte ir_getdir() {
  byte res = 0;
  
  if (ir_inhitzone(3)) { // back
    res = 2;
  }
  
  if (ir_inhitzone(0)) { // right
    res = 4;
  } else if (ir_inhitzone(1)) { // center
    res = 1;
  } else if (ir_inhitzone(2)) { // left
    res = 3;
  }
  
  return res;
}
/* /IR follow logic */

void ir_setup() {
}

void serial_output_ir() {
  Serial.print("{\"irsensors\": ");
  Serial.print(IR_COUNT, DEC);
  Serial.print(", \"values\": [");
  
  for (int irIdx = 0; irIdx < IR_COUNT; irIdx++) {
    Serial.print( ((int)(irValues[irIdx] * 1000.0)) / 1000.0 , DEC); // truncate after 3 decimal points
    if (irIdx < (IR_COUNT - 1)) {
      Serial.print(", ");
    }
  }
  
  Serial.println("]}");
}
