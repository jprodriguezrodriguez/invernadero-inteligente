#include <Wire.h>
#define DS1307_I2C_ADDRESS 0X68
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

/** Funcion para Leer el RTC ***/
void getDateDs1307(
  byte *second,
  byte *minute,
  byte *hour,
  byte *dayOfWeek,
  byte *dayOfMonth,
  byte *month,
  byte *year) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

/** Funcion para Escribir en el RTC ***/
void setDateDs1307(byte second,      // 0-59
                   byte minute,      // 0-59
                   byte hour,        // 0-23
                   byte dayOfWeek,   // 1-7
                   byte dayOfMonth,  // 1-28/29/30/31
                   byte month,       // 1-12
                   byte year)        // 0-99
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));  // 0 to bit 7 starts the clock
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));  // If you want 12 hour am/pm you need to set
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

// -- Función para imprimir en pantalla la Hora y Fecha
void printDateHour() {
  // updateClock();
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Date:");
  // lcd.print(dayOfMonth, DEC);
  // lcd.print("/");
  // lcd.print(month, DEC);
  // lcd.print("/");
  // lcd.print(year, DEC);
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);

  for (int i = 0; i < 10; i++) {
    getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    Serial.print("hora:");
    Serial.println(hour, DEC);
    Serial.print("minutos:");
    Serial.println(minute, DEC);
    Serial.print("segundos:");
    Serial.println(second, DEC);
    // lcd.setCursor(0, 1);
    // lcd.print("Hour:");
    // lcd.print(hour, DEC);
    // lcd.print(":");
    // lcd.print(minute, DEC);
    // lcd.print(":");
    // lcd.print(second, DEC);
    delay(990);
    Serial.print("día de la semana:");
    Serial.println(dayOfWeek, DEC);
  }
}

// -- Función para actualizar la fecha y hora con la fecha y hora actual
void updateClock() {
  dayOfMonth = 0x14;
  month = 0x05;
  year = 0x19;
  dayOfWeek = 0x03;
  hour = 0x07;
  minute = 0x05;
  second = 0x00;

  setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}