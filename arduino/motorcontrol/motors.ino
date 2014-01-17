#define M_M1 4
#define M_E1 5
#define M_M2 7
#define M_E2 6
#define M_SPEED 175

volatile short m_cnt[] = {0, 0};

unsigned int rpm[] = {0, 0};
unsigned long m_tim_last[] = {0, 0};

/* Motor controls */
void motor_stop(void) {
  digitalWrite(M_E1, LOW);
  digitalWrite(M_E2, LOW);
}

// move forward
void motor_advance(char a, char b) {
  analogWrite(M_E1, a);
  digitalWrite(M_M1, HIGH);
  analogWrite(M_E2, b);
  digitalWrite(M_M2, LOW);
}

void motor_back(char a, char b) {
  analogWrite(M_E1, a);
  digitalWrite(M_M1, LOW);
  analogWrite(M_E2, b);
  digitalWrite(M_M2, HIGH);
}

void motor_left(char a, char b) {
  analogWrite(M_E1, a);
  digitalWrite(M_M1, LOW);
  analogWrite(M_E2, b);
  digitalWrite(M_M2, LOW);
}

void motor_right(char a, char b) {
  analogWrite(M_E1, a);
  digitalWrite(M_M1, HIGH);
  analogWrite(M_E2, b);
  digitalWrite(M_M2, HIGH);
}
/**/

void motor_setup(void) {
  for (int mIdx = 4; mIdx <= 7; mIdx++) {
    pinMode(mIdx, OUTPUT);
  }
  
  m_tim_last[0] = millis();
  m_tim_last[1] = m_tim_last[1];
  
  attachInterrupt(0, intr_m1, RISING); // D2
  attachInterrupt(1, intr_m2, RISING); // D3 
  
  motor_stop();
}

void intr_m1(void) {
  m_cnt[0]++;
}

void intr_m2(void) {
  m_cnt[1]++;
}

void motor_read_update(byte idx) {
  // TODO clean up this mess
  unsigned long tim_cur = millis();
  unsigned int tim_diff = tim_cur - m_tim_last[idx]; 
  if (m_cnt[idx] >= 25) {
    rpm[idx] = 30*1000 / tim_diff * m_cnt[idx];
    if (tim_diff > 500) {
      m_tim_last[idx] = tim_cur;
      m_cnt[idx] = 0;
    }
  } else if (tim_diff > 500) {
    rpm[idx] = 0;
  }
}

void motor_read(void) {
  motor_read_update(0);
  motor_read_update(1);
}

void motor_control() {  
  // control indicator (0 == stop)
  byte m_ctl = 0; 
  // set speed for default and fallback commands
  byte m_velocity = M_SPEED;
  
  m_ctl = get_keycommand();
  
  if (m_ctl == 0) {
    // follow close objects
    m_ctl = ir_getdir();
  }
  
  // front bumpers
  if (bumper_hit()) {
    // move back when bumper was hit
    m_ctl = 2;
  }
  
  // prevent forward motion when front IR registers close object
  if (m_ctl == 1 && ir_tooclose_front()) m_ctl = 0;
  // prevent backward motion when back IR registers close object
  if (m_ctl == 2 && ir_tooclose_back()) m_ctl = 0;
  
  // switch control result
  switch (m_ctl) {
    case 1:
      motor_advance(m_velocity, m_velocity);
      break;
    case 2:
      motor_back(m_velocity, m_velocity);
      break;
    case 3:
      motor_left(m_velocity, m_velocity);
      break;
    case 4:
      motor_right(m_velocity, m_velocity);
      break;
    case 0:
    default:
      motor_stop();
  }
}

void serial_output_motors() {
  Serial.print("{\"motorRPM\": [");
  Serial.print(rpm[0], DEC);
  Serial.print(", ");
  Serial.print(rpm[1], DEC);
  Serial.println("]}");
}
