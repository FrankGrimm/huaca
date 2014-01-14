char serial_buffer[SERVO_COUNT * 3 + 2];

int serialIdx = 0;

void serial_process() {
  char current;
  serial_buffer[SERVO_COUNT * 3 + 1] = '\0';
  
  while (Serial.available() && current != '\n' && serialIdx < (SERVO_COUNT * 3 + 1)) {
    current = Serial.read();
    if (current == 'S') serialIdx = 0;
    
    if (serialIdx == 0) {
      if (current == 'S') {
        serial_buffer[serialIdx++] = current;
      }
    } else if (serialIdx > (SERVO_COUNT * 3 + 1)) {
      serialIdx = 0;
    } else {
      if (serial_buffer[0] == 'S' && current >= '0' && current <= '9') {
        serial_buffer[serialIdx++] = current;
      }
    }
  }
 
  if (serial_buffer[0] == 'S' && serialIdx >= (SERVO_COUNT * 3 + 1)) {   
    char targetString[4];
    
    for (int servoIdx = 0; servoIdx < SERVO_COUNT; servoIdx++) {
      for (int bufIdx = 0; bufIdx < 3; bufIdx++) {
        targetString[bufIdx] = serial_buffer[servoIdx * 3 + bufIdx + 1];
      }
      targetString[3] = '\0';
      int target = atoi(targetString);
      if (target <= 180 && target >= 0) {
        servo_set_target(servoIdx, target);
      }
    }
    
    Serial.print("{\"command\": \"move\", \"params\": \"");
    Serial.print(serial_buffer);
    Serial.println("\"}");
    
    // reset command char
    serial_buffer[0] = '\0';
    serialIdx = 0;
  }

}

void serial_setup() {
  Serial.begin(9600);
  delay(50);
  Serial.print("{\"init\": \"HEADCONTROLLER\", \"servos\": ");
  Serial.print(SERVO_COUNT, DEC);
  Serial.println("}");
  
  for (int serialIdx = 0; serialIdx < 10; serialIdx++) {
    serial_buffer[serialIdx] = '\0';
  }
}
