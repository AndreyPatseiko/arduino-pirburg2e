/*
  Привод ХХ
  Нужно подключить сервопривод и установить угол 90 - это будет нулевой точкой (уже прописано в setup: true)
  хвоставик дожен касатся газового упора
  Диапазон регулировки от 180 до 15 градусов. Рабочий диапазон от 100 до 55.
  Если значяение меньше 55 то может проскочить через ограничитель!
*/

int enginWarmTemperatureForIdling = 45;  // t - при которой полностью убираем подсос

// Переменные для холостого хода
Servo idlingServo;                  // называем серво
int idlingPin = 9;                  // пин подключения серво
int setupIdlingAngle = 105;         // угол для первоночальной установки
float minIdlingServoDeg = 65;       // XX - максимальные прогревочные
float maxIdlingServoDeg = 105;      // XX - прогревочные выключены
float idlingAngelForOneDegree = ((maxIdlingServoDeg - minIdlingServoDeg) / enginWarmTemperatureForIdling); // угол одно градуса

void controlIdlingServo(bool setupMode, int temperature) {
  float idlingServoAngle = idlingServo.read();
  if (setupMode) {
    if (idlingServoAngle != setupIdlingAngle) {
      // если initmode и угол не равен необходимому
      runIdlingServo(setupIdlingAngle);
    }
  } else {
    if (temperature <= enginWarmTemperatureForIdling) {
      // рабочий цикл
      runIdlingServo(getIdlingAngelFromDegree(temperature));
    }
    else if (temperature > enginWarmTemperatureForIdling && idlingServoAngle != maxIdlingServoDeg) {
      // все прогрелось
      runIdlingServo(maxIdlingServoDeg);
      delay(1000);
      idlingServo.detach();
    } else {
      idlingServo.detach();
    }
  }
}

int getIdlingAngelFromDegree(int temperature) {
  if (temperature <= 0) {
    return minIdlingServoDeg; // максимальные прогревочные
  }
  else if (temperature > 0 && temperature < enginWarmTemperatureForIdling) {
    return minIdlingServoDeg + (idlingAngelForOneDegree * temperature);
  }
  else {
    return maxIdlingServoDeg; // прогревочные выключены
  }
};

void runIdlingServo(int angle) {
  Serial.print("idlingServoAngle ");
  Serial.println(angle);
  if (angle >= minIdlingServoDeg || angle <= maxIdlingServoDeg) {
    idlingServo.write(angle);
  }
  else if (angle < minIdlingServoDeg) {
    idlingServo.write(minIdlingServoDeg);
  }
  else if (angle > maxIdlingServoDeg) {
    idlingServo.write(maxIdlingServoDeg);
  }
  idlingServo.attach(idlingPin);
}
