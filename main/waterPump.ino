
void activeWaterPump() {
  digitalWrite(WATER_PUMP_RELAY_PIN, HIGH);
}

void deactivateWaterPump() {
  digitalWrite(WATER_PUMP_RELAY_PIN, LOW);
}

void testWaterPump() {
  Serial.println("SENDING LOW");
  digitalWrite(WATER_PUMP_RELAY_PIN, LOW);  // Enciende la bomba
  delay(10000);

  Serial.println("SENDING HIGH");
  digitalWrite(WATER_PUMP_RELAY_PIN, HIGH); // Apaga la bomba
  delay(3000);
}
