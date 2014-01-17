int relayPin = 10;
boolean relayActive = false;
#define RELAY_DELAY_MS 100

void relay_setup() {
  pinMode(relayPin, OUTPUT);
  
  if (relayActive) {
      analogWrite(relayPin, 0);
    } else {
      analogWrite(relayPin, 255);
    }
}

void relay_control() {
  if (relayCommand == 1) {
    // enable
    relay_set(true);
  } else if (relayCommand == 2) {
    // disable
    relay_set(false);
  }
}

void relay_set(boolean active) {
  if (active != relayActive) {
    // value changed
    relayActive = active;
    if (relayActive) {
      analogWrite(relayPin, 0);
    } else {
      analogWrite(relayPin, 255);
    }
    delayMicroseconds(RELAY_DELAY_MS);
    serial_output_relay(true);
  }
}

void serial_output_relay(boolean setValue) {
  Serial.print("{\"relayActive\": ");
  if (relayActive) {
    Serial.print("true");
  } else {
    Serial.print("false");
  }
  if (setValue) {
    Serial.print(", \"set\": true");
  }
  Serial.println("}");
}

