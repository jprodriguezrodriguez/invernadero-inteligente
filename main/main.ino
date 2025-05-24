#include <Wire.h>
#include <dht11.h>
#include <LiquidCrystal.h>

// Configuración de pines: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// MICRO SD
#include <SD.h>
#include <SPI.h>
int pinCS = 49;
File testFile;
int reportNumber = 0;
int date[7];
File reportFile;
char filename[20];

// Sensores
float groundHumidityOne = 0;
float groundHumidityTwo = 0;
float groundHumidityThree = 0;

// Water Pump
#include <Arduino.h>
const int WATER_PUMP_RELAY_PIN = 34;
boolean waterPumpOn = false;

// DTMF
char teclaDTMF = 0;

// Temperatura y Humedad
float ambientTemperature = 0.0;
float ambientHumidity = 0.0;

// Luz UV
int readUVLight = 0;

// Fan
boolean fanOn = false;

void setup() {
  Serial.begin(9600);

  Wire.begin();

  // Setup buzzer
  pinMode(buzzerInput, OUTPUT);

  // Setup LCD
  lcd.begin(16, 2);

  // Setup MicroSD
  pinMode(pinCS, OUTPUT);
  Serial.println("\nInicializando tarjeta SD");
  do {
    if (!SD.begin(pinCS)) {
      Serial.println("Inserte la memoria SD en el socket");
    }
  } while (!SD.begin(pinCS));

  Serial.println("SD conectada");

  // Water Pump
  pinMode(WATER_PUMP_RELAY_PIN, OUTPUT);

  // Fan initialize
  pinMode(FAN_RELAY_PIN, OUTPUT);

  //DTMF Initialize
  pinMode(STQ, INPUT);
  pinMode(Q1, INPUT);
  pinMode(Q2, INPUT);
  pinMode(Q3, INPUT);
  pinMode(Q4, INPUT);
}

// -- FUNCIONES GLOBALES -- //
byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) {
  return ((val / 16) * 10 + (val % 16));
}
void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INVERNADERO");
  lcd.setCursor(0,1);
  lcd.print("GRUPO 11");
  delay(2000);

  groundHumidityOne = getGroundHimidityOne();
  groundHumidityTwo = getGroundHimidityTwo();
  groundHumidityThree = getGroundHimidityThree();

  bool dry1 = isOneDry();
  bool dry2 = isTwoDry();
  bool dry3 = isThreeDry();

  Serial.println("¿UNO ESTÁ SECO?");
  Serial.println(dry1);

  Serial.println("DOS ESTÁ SECO?");
  Serial.println(dry2);

  Serial.println("TRES ESTÁ SECO?");
  Serial.println(dry3);

  Serial.print("HUMEDAD SUELO SENSOR UNO 🪴: ");
  Serial.println(groundHumidityOne);
  Serial.print("HUMEDAD SUELO SENSOR DOS ☘️: ");
  Serial.println(groundHumidityTwo);
  Serial.print("HUMEDAD SUELO SENSOR TRES 🌾: ");
  Serial.println(groundHumidityThree);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HUM S1:");
  lcd.print(groundHumidityOne);
  lcd.setCursor(0, 1);
  lcd.print("HUM S2:");
  lcd.print(groundHumidityTwo);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HUM S2:");
  lcd.print(groundHumidityTwo);
  lcd.setCursor(0, 1);
  lcd.print("HUM S3:");
  lcd.print(groundHumidityThree);
  delay(2000);

  if (dry1 && dry2 && dry3) {
    Serial.println("ACTIVANDO SISTEMA DE RIEGO 🐳");
    activeWaterPump();
    lcd.clear();
    getWaterPumpActivate();
    waterPumpOn = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  ACTIVANDO");
    lcd.setCursor(0, 1);
    lcd.print("   RIEGO");

    while (isOneDry() && isTwoDry() && isThreeDry()) {
      getGroundHimidityOne();
      getGroundHimidityTwo();
      getGroundHimidityThree();

      Serial.println("... REGANDO 🐳... ");
      delay(2000);
    }

    Serial.println("TERRENO HÚMEDO DETECTADO 🛑");
    deactivateWaterPump();
    getWaterPumpActivate();
    waterPumpOn = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" DESACTIVANDO");
    lcd.setCursor(0, 1);
    lcd.print("     RIEGO");

  } else {
    Serial.println("SUELO SUFICIENTEMENTE HÚMEDO 🐳");
    deactivateWaterPump();
    getWaterPumpActivate();
    waterPumpOn = false;
  }

  ambientTemperature = getTemperatureValues();
  ambientHumidity = getHumidityValues();

  Serial.print("Temperature (C): ");
  Serial.println(ambientTemperature);
  Serial.print("Humedad (H): ");
  Serial.println(ambientHumidity);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.print(ambientTemperature);
  lcd.setCursor(0, 1);
  lcd.print("HUM:");
  lcd.print(ambientHumidity);
  delay(4000);

  if (ambientTemperature > 19.00 && ambientTemperature < 24.00) {
    getTemperatureSound();
    Serial.println("Es necesario activar el ventilador");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   ENCIENDA EL");
    lcd.setCursor(0, 1);
    lcd.print("   VENTILADOR");

    // Espera activa para detectar la tecla durante 3 segundos
    unsigned long startTime = millis();
    while (millis() - startTime < 3000) {
      if (digitalRead(STQ) == HIGH) {
        teclaDTMF = decodificarDTMF();
        if (teclaDTMF) {
          Serial.print("DTMF detectado: ");
          Serial.println(teclaDTMF);
          break;
        }
      }
    }

    if (teclaDTMF == '1') {
      runFan();
      Serial.println("ENCENDER VENTILADOR 😶‍🌫️");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   VENTILADOR");
      lcd.setCursor(0, 1);
      lcd.print("   ENCENDIDO");
      fanOn = true;
    }
    teclaDTMF = 0;
  } else {
    getTurnOffTemperatureSound();
    Serial.println("Ya puede apagar el ventilador");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    APAGUE EL");
    lcd.setCursor(0, 1);
    lcd.print("   VENTILADOR");
    // Espera activa para detectar la tecla durante 3 segundos
    unsigned long startTime = millis();
    while (millis() - startTime < 3000) {
      if (digitalRead(STQ) == HIGH) {
        teclaDTMF = decodificarDTMF();
        if (teclaDTMF) {
          Serial.print("DTMF detectado: ");
          Serial.println(teclaDTMF);
          break;
        }
      }
    }

    if (teclaDTMF == '0') {
      stopFan();
      getTurnOffTemperatureSound();
      Serial.println("APAGANDO VENTILADOR 😶‍🌫️");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   VENTILADOR");
      lcd.setCursor(0, 1);
      lcd.print("   APAGADO");
      fanOn = false;
    }
  }

  readUVLight = getCurrentUVLight();

  Serial.println("== REPORTES ==");
  createReport();
  lcd.clear();


  saveReportToSD(0x01);
  delay(10000);
}