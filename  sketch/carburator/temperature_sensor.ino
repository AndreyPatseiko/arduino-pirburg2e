// Чтение сопротивления датчика темперетуры
float getOms() {
  int analogPin = 0;  // пин к корому подключается датчик 5;
  int Vin = 5;        // опорное напряжение
  float R1 = 1000;    // сопротивление известного резистора
  float R2 = 0;       // сопротивление измеряемого резистора (нашего датчика температуры)
  float buffer = analogRead(analogPin) * Vin;
  float Vout = (buffer) / 1024.0;
  buffer = (Vin / Vout) - 1;
  return R1 * buffer;
}

// Преобразование сопротивления в обычную температуру
float omsToTemperature(float oms) {
//  int t = 0;
//  if (oms > 3792 ) { // < 20
//    t = -0.0058 * oms + 33.4788;
//  }
//  else if (oms < 3792  && oms >= 2500 ) { // 10 20
//    t = -0.0077 * oms + 39.3498;
//  }
//  else if (oms < 2500  && oms >= 595 ) { // 20 - 60
//    t = -0.0202 * oms + 67.5426;
//  }
//  else if (oms < 595 ) { // > 60
//    t = -0.1197 * oms + 124.8946;
//  }
  float t = (82000. - 80. * oms)/660.;
  return t;
}
