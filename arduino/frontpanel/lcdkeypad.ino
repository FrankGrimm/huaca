/*
 * PINs as given in example LCDKeypad\LCD1602:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD BL pin to digital pin 10
 * KEY pin to analogl pin 0
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

char msgs[5][16] = {"RIGHT",
                    "UP",               
                    "DOWN",
                    "LEFT",
                    "SELECT" };

int adc_key_val[5] ={50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

void setup_lcd() {
  lcd.clear(); 
  lcd.begin(16, 2);
}

void lcd_settext(byte line, char* text) {
  lcd.setCursor(0,line); 
  lcd.print(text); 
}

void lcd_on(boolean onoff) {
  if (onoff) {
    lcd.display();
  } else {
    lcd.noDisplay();
  }
}

/*
 * Handle keystrokes
 */
void lcd_readkey() {
  adc_key_in = analogRead(0);    // read the value from the sensor 
  key = get_key(adc_key_in);  // convert into key press
 
  if (key != oldkey)   // if keypress is detected
   {
    delay(50);  // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor 
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey)    
    {
      oldkey = key;
      if (key >=0){
           lcd_settext(1, msgs[key]);
           Serial.print("{\"keyEvent\": \"");
           Serial.print(msgs[key]);
           Serial.println("\"}");
      }
    }
  }
}

/* Convert ADC value to key number
 * See example LCDKeypad\LCD1602
 */
int get_key(unsigned int input)
{
    int k;
   
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
 {
            return k;
        }
   }
   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
}

