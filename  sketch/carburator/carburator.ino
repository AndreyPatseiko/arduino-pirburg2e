/*
   При первой установке нужно - либо установить параметр setupServo = true, или передать через терминал команду setup: true|
   При первоначальной настройке.

   Привод ХХ
   нужно подключить сервопривод и установить угол 90 - это будет нулевой точкой (уже прописано в setup: true)
   Диапазон регулировки от 180 до 15 градусов. Рабочий диапазон от 100 до 55.
   Если значяение меньше 55 то может проскочить через ограничитель!

   Привод Воздушной заслонки.
   При servoSetup = true, устанавилвается в положение 0. При этом нужно перевести серво в режим полной открытой
   воздушной заслонки.

   Регулировка параметров нужно использовать.
   c: (0-50) |        угол воздушной завслонки
   h: ((100-180)-55)| угол подпора ХХ
   setup: true|       переключение в режим настройки\работы. При каждом вызове setup: true| - уставливает сервоприводы в необходимые положения.
   wt: int |          изменить время прогревочного цикла ( параметр в мск)

   Расчет для параметров датчика температуры тазбит на два сегмента(для линейного подсчета)
   >5500 om - 1000om - прогрвается двигатель (t = -5 - +40 C)
   <1000 om - 120om - слегка прогрелся но еще не рабочая температура
*/ 


#define modePin 8           // переключатель в stupmode
#include <Servo.h>          //используем библиотеку для работы с сервоприводом

bool setupMode = false;    // режин настройки привода
unsigned long timer = 0;
unsigned long checkInterval = 3000; // инервал когда нужно змерять сопротивление и выполнить цикл, через каждые 15 сек;

void setup() {
  Serial.begin(9600);
  pinMode(modePin, INPUT);
  setupRpm();             // теперь можно запрашивать обрты через переменную rpm
}

void loop() {    
  if(runFromDelay()){    
    setupMode = digitalRead(modePin);   
    float sensorOms = getOms();
    float temperature = omsToTemperature(sensorOms);
    Serial.print("setupMode ");
    Serial.print(setupMode);
    Serial.print(" ;sensorOms ");
    Serial.print(sensorOms);
    Serial.print(" ;temperature ");
    Serial.println(temperature);
    controlChokeServo(setupMode, temperature);
    controlIdlingServo(setupMode, temperature);
  }  
}

bool runFromDelay(){
  if(millis() > timer + checkInterval){
    timer = millis();
    return true;
  } else {
    return false;
  }
}
