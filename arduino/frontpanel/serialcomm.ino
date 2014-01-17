#define SERIAL_BAUD 19200

void serial_setup() {
  Serial.begin(19200);
  delay(50);
  Serial.println("{\"init\": \"FRONTPANEL\"}");
  serial_wait();
}

void serial_wait() {
  boolean isEnabled = true;
  while (Serial.available() <= 0) {
    lcd_settext(0, "Waiting...");
    if (isEnabled) {
      isEnabled = false;
      lcd_on(isEnabled);
    } else {
      isEnabled = true;
      lcd_on(isEnabled);
    }
    delay(500);
  }
  lcd_settext(0, "    CONNECT");
  lcd_on(true);
}
