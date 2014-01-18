 // Upload as Duemilanove w/ ATmega328
// 19200 baud
// see serial_read() for command codes

#define LOOP_DELAY 100
void setup() {
  serial_setup();
  ir_setup();
  bumpers_setup();
  relay_setup();
  motor_setup();
}

void loop() {
  // read sensors
  ir_read_all(); 
  bumpers_read_all();
  motor_read();
  
  // read serial
  serial_read();
  
  // act and report status
  motor_control();
  relay_control();
  serial_output();
  
  // delay loop
  delay(LOOP_DELAY);
}

byte serialCommand = -1;
byte relayCommand = -1;

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
    
    serialCommand = -1;
    relayCommand = -1;
    if (r > 20) {
      switch (r) {
        case 97: // a - turn left
          serialCommand = 3;
          break;
        case 119: // w - move forward
          serialCommand = 1;
          break;
        case 100: // d - turn right
          serialCommand = 4;
          break;
        case 115: // s - move backward
          serialCommand = 2;
          break;
        case 114: // r - stop motor movement
          serialCommand = 0;
          break;
        case 116: // t - enable relay
          relayCommand = 1;
          break;
        case 103: // g - disable relay
          relayCommand = 2;
          break;
        case 117:
          serialCommand = 9;
          break;
        case 105: // i - high speed mode
          serialCommand = 5;
          break;
        case 107: // k - regular speed mode
          serialCommand = 6;
          break;
        default:
          serialCommand = -1;
          relayCommand = -1;
      }
      
      Serial.print("{\"rcvKey\": ");
      Serial.print(r, DEC);
      Serial.print(", \"cmd\": ");
      Serial.print(serialCommand, DEC);
      Serial.println("}");
    }
  }
}

void serial_output() {
  serial_output_ir();
  serial_output_bumpers();
  serial_output_motors();
  serial_output_relay(false);
}
