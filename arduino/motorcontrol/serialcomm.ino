#define SERIAL_BAUD 19200

void serial_setup() {
  Serial.begin(19200);
  Serial.println("{\"init\": \"ROBOTBASE\"}");
}
