const int FAN_RELAY_PIN = 48;

void runFan() {
  digitalWrite(FAN_RELAY_PIN, HIGH);
}

void stopFan() {
  digitalWrite(FAN_RELAY_PIN, LOW);
}

// the loop function runs over and over again forever
void testFan() {
  Serial.println("ENCENDIENDO VENTILADOR - HIGH");
  digitalWrite(FAN_RELAY_PIN, HIGH);
  delay(5000);
  Serial.println("APAGANDO VENTILADOR - LOW");
  digitalWrite(FAN_RELAY_PIN, LOW);
  delay(5000);
}