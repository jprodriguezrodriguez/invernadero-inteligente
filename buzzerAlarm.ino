const int buzzerInput = 38;

void getWaterPumpActivate() {
  delay(1000);
  tone(buzzerInput, 1000);
  delay(1000);
  noTone(buzzerInput);
}

void createReport() {
  delay(100);
  tone(buzzerInput, 2000);
  delay(100);
  noTone(buzzerInput);
  delay(100);
  tone(buzzerInput, 2000);
  delay(100);
  noTone(buzzerInput);
}

void savedReport() {
  delay(1000);
  tone(buzzerInput, 2000);
  delay(1000);
  noTone(buzzerInput);
}

void getTemperatureSound() {
  delay(100);
  tone(buzzerInput, 200);
  delay(100);
  noTone(buzzerInput);
  delay(100);
  tone(buzzerInput, 200);
  delay(100);
  noTone(buzzerInput);
}

void getTurnOffTemperatureSound() {
  delay(100);
  tone(buzzerInput, 600);
  delay(100);
  noTone(buzzerInput);
  delay(100);
  tone(buzzerInput, 600);
  delay(100);
  noTone(buzzerInput);
  delay(100);
  tone(buzzerInput, 600);
  delay(100);
  noTone(buzzerInput);
}