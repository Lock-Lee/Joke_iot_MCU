void door(int state)
{
  if (state == 1)

  {

    if (readLux  < set_lux_start && readLux < set_lux_end && set_lux_end > set_lux_start)
    {
      Serial.println("on Door");
      rond = 2;
    }
    else if (readLux  > set_lux_start && readLux > set_lux_end && set_lux_end > set_lux_start)
    {
      Serial.println("off Door");
      rond = 1;
    }
    else if (readLux >= set_lux_start  && readLux <= set_lux_end )
    {
      rond = 0;
    }

    if (checkDoor == 0 && rond == 1)
    {
      while (1)
      {
        readSensor();
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval && checkDoor == 0)
        {
          previousMillis = currentMillis;
          sec++;
        }
        else if (sec < 16 && checkDoor == 0)
        {
          digitalWrite(reLayMotorR, 0);
          digitalWrite(reLayMotorL, 1);
        }
        else if (sec > 16)
        {
          status_door = 1;
          checkDoor = 1;
          sec = 0;
          led01 = 0;
          digitalWrite(reLayLed, 0);
          digitalWrite(reLayMotorR, 0);
          digitalWrite(reLayMotorL, 0);
          break;
        }
      }
    }

    if (checkDoor == 1 && rond == 2)
    {
      while (1)
      {
        readSensor();

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
          previousMillis = currentMillis;
          sec++;
        }
        else if (sec < 16 && checkDoor == 1)
        {

          digitalWrite(reLayMotorR, 1);
          digitalWrite(reLayMotorL, 0);
        }
        else if (sec > 16)
        {
          checkDoor = 0;
          sec = 0;
          led01 = 1;

          digitalWrite(reLayMotorR, 0);
          digitalWrite(reLayMotorL, 0);
          break;
        }
      }
      if (led01 == 1 && checkDoor == 0)
      {
        if (readLux < (set_lux_end))
        {
          digitalWrite(reLayLed, 1);
          status_light = 1;
        }
        else
        {
          digitalWrite(reLayLed, 0);
          status_light = 0;
        }
      }
    }
  }
  if (state == 0)
  {

    status_door = 0;
    Serial.println("stop");
    digitalWrite(reLayLed, 0);
    digitalWrite(reLayMotorR, 0);
    digitalWrite(reLayMotorL, 0);
  }
}
void doormanully(char state)
{
  if (state == '1')
  {
    rond = 1;
    checkDoor = 0;
  }
  else if (state == '2')
  {
    rond = 2;
    checkDoor = 1;
  }
  if (checkDoor == 0 && rond == 1)
  {
    while (1)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > interval && checkDoor == 0)
      {
        previousMillis = currentMillis;
        sec++;
        Serial.print("1 = ");
        Serial.println(sec);
      }
      else if (sec < 12 && checkDoor == 0)
      {
        digitalWrite(reLayMotorR, 1);
        digitalWrite(reLayMotorL, 0);
      }
      else if (sec > 12)
      {

        checkDoor = 1;
        status_door = 1;
        sec = 0;
        digitalWrite(reLayMotorR, 0);
        digitalWrite(reLayMotorL, 0);
        break;
      }
    }
  }
  else
  {
  }
  if (checkDoor == 1 && rond == 2)
  {
    while (1)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > interval)
      {
        previousMillis = currentMillis;
        sec++;
        Serial.print("2 = ");
        Serial.println(sec);
      }
      else if (sec < 12 && checkDoor == 1)
      {
        digitalWrite(reLayMotorR, 0);
        digitalWrite(reLayMotorL, 1);
      }
      else if (sec > 12)
      {
        status_door = 0;
        checkDoor = 0;
        sec = 0;
        digitalWrite(reLayMotorR, 0);
        digitalWrite(reLayMotorL, 0);
        break;
      }
    }
  }
  else
  {
  }
}
