 // Upload as Duemilanove w/ ATmega328
// 19200 baud
#define LOOP_DELAY 100
void setup() {
  serial_setup();
  ir_setup();
  bumpers_setup();
  motor_setup();
}

void loop() {
  // read sensors
  ir_read_all(); 
  bumpers_read_all();
  motor_read();
  
  // read serial
  serial_read();
  
  // act
  motor_control();
  
  serial_output();
  
  // delay loop
  delay(LOOP_DELAY);
}

byte serialCommand = -1;

byte get_keycommand() {
  byte res = 0;
  
  if (serialCommand > -1) {
    return serialCommand;
  }
  
  serialCommand = -1;
  
  return res;
}

void serial_read() {
  while (Serial.available()) {
    short r = Serial.read();
    if (r > 20) {
      switch (r) {
        case 97:
          serialCommand = 3;
          break;
        case 119:
          serialCommand = 1;
          break;
        case 100:
          serialCommand = 4;
          break;
        case 115:
          serialCommand = 2;
          break;
        case 114:
          serialCommand = 0;
          break;
        default:
          serialCommand = -1;
      }
      
      Serial.print("{\"rcvKey\": ");
      Serial.print(r, DEC);
      Serial.println("}");
    }
  }
}

void serial_output() {
  serial_output_ir();
  serial_output_bumpers();
  serial_output_motors();
}
