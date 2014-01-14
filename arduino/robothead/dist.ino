const byte irPin = A3; // ir sensor on analog input 3

// http://www.arduino.cc/playground/Main/ReadGp2d12Range
// output: cm
float gp2d12_range(byte pin) {
  int tmp;
  tmp = analogRead(pin);
  if (tmp < 3)
    return -1; // invalid value
  return (6787.0 /((float)tmp - 3.0)) - 4.0;
}

float gp2d12_range_avg(byte pin, byte runs) {
  float sum;
  
  for (byte r = 0; r < runs; r++) {
    int tmp;
    tmp = analogRead(pin);
    if (tmp < 3)
      sum = sum + 0.0; // invalid value
    sum = sum + (6787.0 /((float)tmp - 3.0)) - 4.0;
    delayMicroseconds(10);
  }
  
  return sum / (float)runs;
}

void dist_setup() {
}

void dist_report() {
  print_dist(gp2d12_range(irPin));
  print_dist(gp2d12_range_avg(irPin, 5));
}

void print_dist(float distVal) {
  if (distVal < 0.0 || distVal > 800.0) {
    distVal = -1; // too uncertain, discard value
  }
  Serial.print("{\"ir_dist_0\": ");
  Serial.print(distVal, DEC);
  Serial.println("}");
}
