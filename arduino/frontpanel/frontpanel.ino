// Upload as Arduino UNO
// 19200 baud

// Serial commands:
// "0<TEXT>" Show <TEXT> on line 1
// "1<TEXT>" Show <TEXT> on line 2
// <TEXT> may be empty, clears the line
// omitting the line number default to line 1
//
// LCDON  - Turn display on
// LCDOFF - Turn display off

void setup()
{
  setup_lcd();
  serial_setup();
}

void loop()
{
  lcd_readkey();
  serial_readln();
  delay(100);
}

#define SERIAL_BUFLEN 50
#define SERIAL_RL_FILL 17
void serial_readln() {
  char buffer[SERIAL_BUFLEN];
  int numchars = 0;
  if(Serial.available()) {
     while(Serial.available() && numchars < (SERIAL_BUFLEN-1))
        buffer[numchars++] = Serial.read();
     while (numchars < SERIAL_RL_FILL) {
       buffer[numchars++] = ' ';
     }
     buffer[numchars++]='\0'; // end buffer
  }

  if(numchars > 0) {
    byte outputline = 0;
    char* outputtext = (char*)buffer;
    if (buffer[0] == '1') {
      outputline = 1;
      outputtext += 1;
      lcd_settext(outputline, outputtext);
    } else if (buffer[0] == 'L' && buffer[1] == 'C' && buffer[2] == 'D') {
      if (buffer[3] == 'O' && buffer[4] == 'N') {
        lcd_on(true);
      } else if (buffer[3] == 'O' && buffer[4] == 'F' && buffer[5] == 'F') {
        lcd_on(false);
      }
    } else {
      // first line (default)
      if (buffer[0] == '0') {
        outputtext += 1;
      }
      lcd_settext(outputline, outputtext);
    }
  }
}
