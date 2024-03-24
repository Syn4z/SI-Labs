FILE lcd_out;
int lcd_put(char c, FILE *f) {
  lcd.write(c);
  return 0;
}

void redirectLCDOutput() {
  lcd.setCursor(0, 0);
  fdev_setup_stream(&lcd_out, lcd_put, NULL, _FDEV_SETUP_WRITE);
  stdout = &lcd_out;
}