#define RPMpin 2      // датчик Холла
long microsold = 0;
int rpm = 0;

void setupRpm() {
  digitalWrite(RPMpin, 1);
  attachInterrupt(0, RPM, FALLING);
}

void RPM () {
  rpm = (1000000.0 / (micros() - microsold)) * 60; // 1 гц = 60об/мин
  microsold = micros();
}
