/*
  Привод Воздушной заслонки.
  При servoSetup = true, устанавилвается в положение 0. При этом нужно перевести серво в режим полной открытой
  воздушной заслонки.
*/

int enginWarmTemperature = 65;    // t - при которой полностью открываем заслонку

// Переменные для дросельной заслонки
Servo chokeServo;                 // называем серво
int chokePin = 10;                // пин подключения серво
float minServoChokeDeg = 0;       // Воздушная заслонка - полностью открыта
float maxServoChokeDeg = 45;      // Воздушная заслонка - польностью закрыта
float chokeAngelForOneDegree = (maxServoChokeDeg / enginWarmTemperature); // угол одно градуса

void controlChokeServo(bool setupMode, int temperature) {
  float chokeServoAngle = chokeServo.read();
  // если initmode и угол не равен необходимому
  if (setupMode) {
    if (chokeServoAngle != minServoChokeDeg) {
      runChokeServo(minServoChokeDeg);
    }
  } else {
    if (temperature <= enginWarmTemperature) {
      // рабочий цикл
      runChokeServo(getChokeAngelFromDegree(temperature));
    }
    else if (temperature > enginWarmTemperature && chokeServoAngle != minServoChokeDeg) {
      // все прогрелось
      runChokeServo(minServoChokeDeg);
      delay(1000);
      chokeServo.detach();
    } else {
      chokeServo.detach();
    }
  }
}

int getChokeAngelFromDegree(int temperature) {
  if (temperature <= 0) {
    return maxServoChokeDeg; // полностью закрыта
  }
  else if (temperature > 0 && temperature < enginWarmTemperature) {
    return maxServoChokeDeg - (chokeAngelForOneDegree * temperature);
  }
  else {
    return minServoChokeDeg; // полностью открыта
  }
};

void runChokeServo(int angle) {
  Serial.print("input angle chokeServo ");
  Serial.println(angle);
  if (angle >= minServoChokeDeg || angle <= maxServoChokeDeg) {
    chokeServo.write(angle);
  }
  else if (angle < minServoChokeDeg) {
    chokeServo.write(minServoChokeDeg);
  }
  else if (angle > maxServoChokeDeg) {
    chokeServo.write(maxServoChokeDeg);
  }
  chokeServo.attach(chokePin);
}
