/*
  описать все данные и индексы ячеек для сохраниня данных
*/

#include <EEPROM.h>

void writeData(int cell, int value) {
  EEPROM.write(cell, value);
  // EEPROM.write(0,195);  // Записать значение 195 в ячейку с адресом 0
}

int readData(int cell) {
  // value=EEPROM.read(0);                   // Считать значение ячейки с адресом 0
  return EEPROM.read(cell);
}
