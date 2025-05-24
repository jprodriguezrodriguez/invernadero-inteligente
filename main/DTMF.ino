#define Q1 9
#define Q2 10
#define Q3 11
#define Q4 12
#define STQ 13

// void setup() {
//   pinMode(STQ, INPUT);
//   pinMode(Q1, INPUT);
//   pinMode(Q2, INPUT);
//   pinMode(Q3, INPUT);
//   pinMode(Q4, INPUT);
// }

char decodificarDTMF() {
  uint8_t number_pressed;
  Serial.println("Leyendo DTMF...");
  if (digitalRead(STQ) == LOW) {
    return 0;
  }

  delay(250);
  number_pressed = (digitalRead(Q1) << 0) | (digitalRead(Q2) << 1) | (digitalRead(Q3) << 2) | (digitalRead(Q4) << 3);

  switch (number_pressed) {
    case 0x01: Serial.println("DTMF: 1"); return '1';
    case 0x02: Serial.println("DTMF: 2"); return '2';
    case 0x03: Serial.println("DTMF: 3"); return '3';
    case 0x04: Serial.println("DTMF: 4"); return '4';
    case 0x05: Serial.println("DTMF: 5"); return '5';
    case 0x06: Serial.println("DTMF: 6"); return '6';
    case 0x07: Serial.println("DTMF: 7"); return '7';
    case 0x08: Serial.println("DTMF: 8"); return '8';
    case 0x09: Serial.println("DTMF: 9"); return '9';
    case 0x0A: Serial.println("DTMF: 0"); return '0';
    case 0x0B: Serial.println("DTMF: *"); return '*';
    case 0x0C: Serial.println("DTMF: #"); return '#';
    default:
      Serial.print("DTMF invalido: ");
      Serial.println(number_pressed);
      return 0;
  }
}

// void loop() {
//   if (digitalRead(STQ) == HIGH) {
//     Serial.println("inside digital read");
//     teclaDTMF = decodificarDTMF();
//     if (teclaDTMF) {
//       // lcd.clear();
//       // lcd.print("DTMF: ");
//       // lcd.print(teclaDTMF);
//       // delay(1000);
//       // lcd.setCursor(0, 1);
//       // lcd.print("Esperando...");
//       Serial.println("Decodificando");
//       Serial.println(teclaDTMF);
//     }
//   }
// }