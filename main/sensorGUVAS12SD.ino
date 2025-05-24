// orden de los sensores 1 -> SIG GND VCC
int getCurrentUVLight() {
  readUVLight = analogRead(22);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LUZ ULTRAVIOLETA");
  lcd.setCursor(0,1);
  lcd.print(readUVLight);
  delay(2000);

  return readUVLight;
}
