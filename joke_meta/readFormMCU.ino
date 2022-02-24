void readFormMCU()
{

  ///  รับค่าจาก nodemcu
  if (mySerial.available())
  {
    String received = mySerial.readStringUntil('\n');
    
     if (!received.indexOf("readLux=")) {
       Serial.println(received);
      readLux = received.substring(8).toInt();


    } else if (!received.indexOf("readTemp=")) {
      Serial.println(received);
      readTemp = received.substring(9).toInt();


    } else if (!received.indexOf("readHumidity=")) {
       Serial.println(received);
      readHum = received.substring(13).toInt();


    }
    //อ่าน จาก nodeMCU ตาม part ที่ส่งมา
    if (!received.indexOf("setLux="))
    {
      String str = received.substring(7);
      String path1 = getSplit(str, ',', 0);
      String path2 = getSplit(str, ',', 1);
      set_lux_start = path1.toInt();
      set_lux_end = path2.toInt();
    }
    else if (!received.indexOf("time1="))
    {
      String str = received.substring(6);

      String start =  getSplit(str, ',', 0);
      String end =  getSplit(str, ',', 1);

      String path1 = getSplit(start, ':', 0);
      String path2 = getSplit(start, ':', 1);

      String path3 = getSplit(end, ':', 0);
      String path4 = getSplit(end, ':', 1);
      set_start1.hour = path1.toInt();
      set_start1.min = path2.toInt();
      set_end1.hour = path3.toInt();
      set_end1.min = path4.toInt();
    }
    else if (!received.indexOf("time2="))
    {
      String str = received.substring(6);
      String start =  getSplit(str, ',', 0);
      String end =  getSplit(str, ',', 1);
      String path1 = getSplit(start, ':', 0);
      String path2 = getSplit(start, ':', 1);
      String path3 = getSplit(end, ':', 0);
      String path4 = getSplit(end, ':', 1);
      set_start2.hour = path1.toInt();
      set_start2.min = path2.toInt();
      set_end2.hour = path3.toInt();
      set_end2.min = path4.toInt();
    }
    else if (!received.indexOf("time3="))
    {
      String str = received.substring(6);
      String start =  getSplit(str, ',', 0);
      String end =  getSplit(str, ',', 1);
      String path1 = getSplit(start, ':', 0);
      String path2 = getSplit(start, ':', 1);
      String path3 = getSplit(end, ':', 0);
      String path4 = getSplit(end, ':', 1);
      set_start3.hour = path1.toInt();
      set_start3.min = path2.toInt();
      set_end3.hour = path3.toInt();
      set_end3.min = path4.toInt();
    }

    else if (!received.indexOf("setTemp="))
    {

      String str = received.substring(8);

      String path1 = getSplit(str, ',', 0);
      String path2 = getSplit(str, ',', 1);
      set_temp_start = path1.toInt();
      set_temp_end = path2.toInt();
    }
    else if (!received.indexOf("Door="))
    {
      String str = received.substring(5);


      if (!str.indexOf("on"))
      {

        doormanully('1');
      }
      if (!str.indexOf("off"))
      {

        doormanully('2');
      }
    }
    else if (!received.indexOf("Evap="))
    {
      String str = received.substring(5);
      Serial.println(str);
      status_evap = str.toInt();
      digitalWrite(reLayFan, status_evap);
      digitalWrite(pumpvax, status_evap);
    }
    else if (!received.indexOf("light="))
    {
      String str = received.substring(6);

      status_light = str.toInt();


      digitalWrite(reLayLed, status_light);
    }
    else if (!received.indexOf("pumpwater="))
    {
      String str = received.substring(10);
      Serial.print("water=");
      Serial.println(str);
      status_pumpwater = str.toInt();


      digitalWrite(pumpwater, status_pumpwater);
    }
  }
}
