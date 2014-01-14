#define LOOP_DELAY 250
#define SERVO_COUNT 2

#define SERIAL_BAUDRATE 9600

void setup() {
  serial_setup();
  rgb_setup();
  servo_setup();
  dist_setup();
}

void loop() {
  serial_process();
  if (!servo_move()) {
    servo_report();
    dist_report();
    delay(LOOP_DELAY);
  } else {
    servo_read();
  }
}

