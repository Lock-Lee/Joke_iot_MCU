
uint16_t LuxSensor()
{
  unsigned long currentMillis = millis();
  if (currentMillis - time > 2000)
  {
    time = currentMillis;
    uint16_t lux = LightSensor.GetLightIntensity();
  }

  return lux;
}

void write_Humidity()
{

  _readHumidity = readHumidity();

  mySerial.println((String) "readHumidity=" + _readHumidity);
}
void write_Temp()
{

  _readTemp = readTemperature();

  mySerial.println((String) "readTemp=" + _readTemp);
}