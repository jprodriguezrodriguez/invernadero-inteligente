
#define DHT11PIN 24

dht11 DHT11;

// Pendiente definir cuánto es el máximo de temperatura y el arduino

float getHumidityValues() {
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.humidity;
}

float getTemperatureValues() {
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}