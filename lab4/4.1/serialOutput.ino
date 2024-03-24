FILE f_out;
int sput(char c, __attribute__((unused)) FILE* f) {
  return !Serial.write(c);
}

void redirectSerialOutput(){
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);
  stdout = &f_out;
}