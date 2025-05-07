#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "config.h"
#include "lcd_display.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdDisplay::lcdInit(){
    lcd.init(I2C_SDA, I2C_SCL); // initialize the lcd to use user defined I2C pins
  lcd.display();
  lcd.backlight();
}

void lcdDisplay::lcdWriteFormatted(String text) {
    int currentLine = 0; // Keep track of the current line (0 or 1)
    lcd.clear();
    lcd.noDisplay();
    lcd.display();
    while (text.length() > 0) {
        // Print at most 16 characters from the string on the current line
        String line = text.substring(0, 16);
        text = text.substring(16); // Remove the printed part of the string

        // Clear the current line and set the cursor
        lcd.setCursor(0, currentLine);
        lcd.print(line);

        // Move to the next line if the current line is full
        if (currentLine == 0) {
            currentLine = 1;
        } else {
            break; // No more lines available on the 16x2 display
        }

        delay(100); 
    }
}

void lcdDisplay::lcdPrintTopBottom(String textTop, String textBottom){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(textTop);
    lcd.setCursor(0,1);
    lcd.print(textBottom);
}