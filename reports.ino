void saveReportToSD(byte userId) {
  // Verificación segura
  File test = SD.open("TEST.TMP", FILE_WRITE);
  if (!test) {
    Serial.println("Error: no se pudo acceder a la tarjeta SD.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Falla SD al escribir");
    return;
  }
  test.close();
  SD.remove("TEST.TMP");

  buildReport();  // Llena date[] con [día, mes, año, hora, minuto, segundo]

  char baseName[10];
  sprintf(baseName, "%02d%02d%02d", date[0], date[1], date[2]);

  int suffix = 1;
  while (suffix < 100) {
    sprintf(filename, "%s%02d.TXT", baseName, suffix);
    Serial.print("Verificando: ");
    Serial.println(filename);
    if (!SD.exists(filename)) {
      break;
    }
    suffix++;
  }

  Serial.print("Guardando en archivo: ");
  Serial.println(filename);

  reportFile = SD.open(filename, FILE_WRITE);
  reportFile = SD.open(filename, FILE_WRITE);
  if (reportFile) {
    Serial.println("Generando reporte inside reportFile");

    reportFile.println("=== REPORTE DE MONITOREO ===");
    reportFile.print("Fecha: ");
    reportFile.print(date[0]);
    reportFile.print("/");
    reportFile.print(date[1]);
    reportFile.print("/");
    reportFile.print(date[2]);
    reportFile.print(" ");
    reportFile.print("Hora: ");
    reportFile.print(date[3]);
    reportFile.print(":");
    reportFile.print(date[4]);
    reportFile.print(":");
    reportFile.println(date[5]);

    reportFile.println("-----------------------------");
    reportFile.print("Sensor Suelo 1: ");
    reportFile.println(groundHumidityOne);
    reportFile.print("Sensor Suelo 2: ");
    reportFile.println(groundHumidityTwo);
    reportFile.print("Sensor Suelo 3: ");
    reportFile.println(groundHumidityThree);
    reportFile.print("Temp Ambiente: ");
    reportFile.println(ambientTemperature);
    reportFile.print("Humedad Amb: ");
    reportFile.println(ambientHumidity);
    reportFile.print("Luz UV: ");
    reportFile.println(readUVLight);
    reportFile.print("Ventilador: ");
    reportFile.println(fanOn ? "ENCENDIDO" : "APAGADO");
    reportFile.print("Bomba de Agua: ");
    reportFile.println(waterPumpOn ? "ENCENDIDA" : "APAGADA");
    reportFile.print("Usuario: ");
    reportFile.println(userId);
    reportFile.println("=============================");

    reportFile.close();
    Serial.println("Reporte escrito y cerrado correctamente.");
  } else {
    Serial.print("Error al abrir: ");
    Serial.println(filename);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ERROR AL GUARDAR");
  }
}


void printReportsForToday() {
  buildReport();  // Para tener la fecha actual
  char baseName[10];
  sprintf(baseName, "%02d%02d%02d", date[0], date[1], date[2]);

  for (int suffix = 1; suffix < 100; suffix++) {
    sprintf(filename, "%s%02d.TXT", baseName, suffix);
    if (!SD.exists(filename)) {
      break;
    }

    reportFile = SD.open(filename);
    if (reportFile) {
      while (reportFile.available()) {
        String linea = reportFile.readStringUntil('\n');
        char buffer[50];
        linea.toCharArray(buffer, sizeof(buffer));

        int campos[8];
        int index = 0;
        char *token = strtok(buffer, "\t");
        while (token != NULL && index < 8) {
          if (index == 0 && token[0] == '#') token++;
          campos[index++] = atoi(token);
          token = strtok(NULL, "\t");
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("#");
        if (campos[0] < 10) lcd.print("0");
        lcd.print(campos[0]);
        lcd.print(" ");
        if (campos[1] < 10) lcd.print("0");
        lcd.print(campos[1]);
        lcd.print("/");
        if (campos[2] < 10) lcd.print("0");
        lcd.print(campos[2]);
        lcd.print("/");
        lcd.print(campos[3]);

        lcd.setCursor(0, 1);
        if (campos[4] < 10) lcd.print("0");
        lcd.print(campos[4]);
        lcd.print(":");
        if (campos[5] < 10) lcd.print("0");
        lcd.print(campos[5]);
        lcd.print(":");
        if (campos[6] < 10) lcd.print("0");
        lcd.print(campos[6]);
        lcd.print("  U:");
        lcd.print(campos[7]);
        delay(1500);
      }
      reportFile.close();
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FIN DE REPORTES");
}

void buildReport() {
  // updateClock();
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  date[0] = dayOfMonth;
  date[1] = month;
  date[2] = year;
  date[3] = hour;
  date[4] = minute;
  date[5] = second;
}