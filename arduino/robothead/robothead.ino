// Arduino Duemilanove w/ ATmega328

#define LOOP_DELAY 250
#define SERVO_COUNT 2

#define SERIAL_BAUDRATE 19200

//C00X000 - X = 0(off), 1(red), 2(green), 3(blue), 4(yellow), 5(purple), 6(aqua)
//SXXXYYY - X = angle vertical, Y = horizontal

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

