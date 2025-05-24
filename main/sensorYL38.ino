// orden de los sensores 1 & 2 -> VCC GND AD A0
// orden de los sensores 3 -> A0 AD GND VCC

int humidity = 0;
float groundOneReading, groundTwoReading,groundThreeReading;

// SENSOR 1
// Seco > 900
// Húmedo < 400

// SENSOR 2
// Seco > 900
// Húmedo < 500

// SENSOR 3
// Seco > 900
// Húmedo < 500

float getGroundHimidityOne() {
  groundOneReading = analogRead(A0);
  // Serial.println("Sensor 1");
  // Serial.println(groundOneReading);
  // delay(2000);
  return groundOneReading;
}

float getGroundHimidityTwo() {
  groundTwoReading = analogRead(A1);
  // Serial.println("Sensor 2");
  // Serial.println(groundTwoReading);
  // delay(2000);
  return groundTwoReading;
}

float getGroundHimidityThree() {
  groundThreeReading = analogRead(A2);
  // Serial.println("Sensor 3");
  // Serial.println(groundThreeReading);
  // delay(2000);
  return groundThreeReading;
}

boolean isOneDry() {
  getGroundHimidityOne();
  if (groundOneReading > 500 ) {
    return true;
  } else {
    return false;
  }
}

boolean isTwoDry() {
  getGroundHimidityTwo();
  if (groundTwoReading > 500 ) {
    return true;
  } else {
    return false;
  }
}

boolean isThreeDry() {
  getGroundHimidityThree();
  Serial.println(groundThreeReading);
  if (groundThreeReading > 500 ) {
    return true;
  } else {
    return false;
  }
}