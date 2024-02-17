#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define LCD_WIDTH 12
#define LCD_HEIGHT 6

extern LiquidCrystal_I2C lcd;

#endif
