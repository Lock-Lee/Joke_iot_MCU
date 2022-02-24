void working()
{

  if (realTime.hour == set_end1.hour && realTime.min == set_end1.min)
  {
    Serial.println("end1");
    statetime1 = 0;
    door(statetime1);
    openFan(statetime1);
  }
  else if ((statetime1 == true) || (realTime.hour == set_start1.hour && realTime.min == set_start1.min))
  {
    Serial.println("start1");
    statetime1 = 1;
    door(statetime1);
    openFan(statetime1);
  }
 
   if (realTime.hour == set_end2.hour && realTime.min == set_end2.min)
  {
 Serial.println("end2");
    startPumpWater(false);
  }else  if (realTime.hour == set_start2.hour && realTime.min == set_start2.min)
  {
   Serial.println("start3");
    startPumpWater(true);
  }
   if (realTime.hour == set_end3.hour && realTime.min == set_end3.min)
  {

    startPumpWater(false);
  }else  if ((realTime.hour == set_start3.hour && realTime.min == set_start3.min))
  {
  
    startPumpWater(true);
  }
}
void startPumpWater(bool state)
{

  if (state == true)
  {
     digitalWrite(pumpwater, 1);
        status_pumpwater = 1;
    }

    if (state == false)
    {
     
      digitalWrite(pumpwater, 0);
      status_pumpwater = 0;
    }
  
}
void openFan(int state)
{
 
  if (state == 1)
  {
    if (readTemp >= set_temp_start && readTemp <= set_temp_end)
    {
      digitalWrite(pumpvax, 0);
      digitalWrite(reLayFan, 0);
      status_evap = 1;
    }
    else if (readTemp >= set_temp_start && readTemp >= set_temp_end && set_temp_start != 0 && set_temp_end != 0)
    {
      digitalWrite(reLayFan, 1);
      digitalWrite(pumpvax, 1);
      status_evap = 1;
    }
//    else
//    {
//      Serial.println("endevap");
//      digitalWrite(pumpvax, 0);
//      digitalWrite(reLayFan, 0);
//      status_evap = 0;
//      status_light = 0;
//    }
  }
  if (state == 0)
  {
    digitalWrite(pumpvax, 0);
    digitalWrite(reLayFan, 0);
    status_evap = 0;
    status_light = 0;
    status_door = 0;
  }
}
