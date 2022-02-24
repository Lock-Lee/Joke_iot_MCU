void readKeypad() {
  key = keypad.getKey();

  if (key == '1') {
    /// set time  1
    lcd.clear();
    settime(1);
    
    readtimeprevi(1);
    set_start1.hour  = read_num (23, 3, 1);
    set_start1.min  = read_num (59, 6, 1);
     Serial.println((String)"timestart1=" + set_start1.hour + ":" + set_start1.min);
   
    readtimeprevi(1);
    set_end1.hour  = read_num (23, 3, 3);
    set_end1.min  = read_num (59, 6, 3);
    Serial.println((String)"timeend1=" + set_end1.hour + ":" + set_end1.min);
    lcd.clear();

  } else if (key == '2') {
    lcd.clear();
    settime(2);
   
    readtimeprevi(2);
    set_start2.hour  = read_num (23, 3, 1);
    set_start2.min  = read_num (59, 6, 1);
     Serial.println((String)"timestart2=" + set_start2.hour + ":" + set_start2.min);
    
    readtimeprevi(2);
    set_end2.hour  = read_num (23, 3, 3);
    set_end2.min  = read_num (59, 6, 3);
    Serial.println((String)"timeend2=" + set_end2.hour + ":" + set_end2.min);
    lcd.clear();

  }

  else if (key == '3') {
    /// set lux
    lcd.clear();
    setLux();
    set_lux_start  = read_num (60000, 3, 1);
    set_lux_end = read_num (60000, 3, 3);
     mySerial.println((String)"setLux=" + set_lux_start );
    lcd.clear();

  }
  else if (key == '4')   {
    lcd.clear();
    /// set temp
    settemp();

    lcd.cursor();
    set_temp_start  = read_num (99, 3, 1);
    set_temp_end  = read_num (99, 9, 1);
    lcd.noCursor();
     mySerial.println((String)"setTemp=" + set_temp_start + "," + set_temp_end);
    lcd.clear();

  } else if (key == '6') {

    checkDoor = 1;

  } else if (key == '7') {
    checkDoor = 0;


  } else if (key == '0') {
    mySerial.println("Reset");
  }

  else {




  }




}
void readtimeprevi(int x) {
  if (x == 2) {
    if (set_start2.hour < 10) {
      lcd.setCursor(3, 1);
      lcd.print((String)"0" + set_start2.hour);
      lcd.print(":");
     
      lcd.setCursor(3, 3);
      lcd.print((String)"0" + set_end2.hour);
      lcd.print(":");
      
    } if (set_start2.hour >= 10) {
      lcd.setCursor(3, 1);
      lcd.print(set_start2.hour);
      lcd.print(":");
     
      lcd.setCursor(3, 3);
      lcd.print(set_end2.hour);
      lcd.print(":");
     

    }
     if (set_start2.min >= 10) {
      lcd.setCursor(6, 1);
      lcd.print(set_start2.min);
     
      lcd.setCursor(6, 3);
      lcd.print(set_end2.min);
      
     

    }
    if (set_start2.min < 10) {
      lcd.setCursor(6, 1);
     
      lcd.print((String)"0" + set_start2.min);
      
      lcd.print((String)"0" + set_end2.min);

    } if (set_start2.hour >= 10) {
      lcd.setCursor(3, 1);
      lcd.print(set_start2.hour);
      lcd.print(":");
      
      lcd.setCursor(3, 3);
      lcd.print(set_end2.hour);
      lcd.print(":");
     

    }
    if (set_start2.min >= 10) {
      lcd.setCursor(3, 1);
      lcd.print(set_start2.hour);
      lcd.print(":");
      
      lcd.setCursor(3, 3);
      lcd.print(set_end2.hour);
      lcd.print(":");
     

    }



  }
  if (x == 1) {

    if (set_start1.hour < 10) {
      lcd.setCursor(3, 1);
      lcd.print((String)"0" + set_start1.hour);
      lcd.print(":");

      lcd.setCursor(3, 3);
      lcd.print((String)"0" + set_end1.hour);
      lcd.print(":");

    }
     if (set_start1.hour >= 10 ) {
      lcd.setCursor(3, 1);
      lcd.print(set_start1.hour);
      lcd.print(":");
     
      lcd.setCursor(3, 3);
      lcd.print(set_end1.hour);
      lcd.print(":");
     

    }

    if (set_start1.min < 10) {
      lcd.setCursor(6, 1);
      lcd.print((String)"0" + set_start1.min);
      lcd.setCursor(6, 3);
      lcd.print((String)"0" + set_end1.min);

    } if (set_start1.hour >= 10 && set_start1.min >= 10) {
      lcd.setCursor(3, 1);
      lcd.print(set_start1.hour);
      lcd.print(":");
      lcd.print(set_start1.min);
      lcd.setCursor(3, 3);
      lcd.print(set_end1.hour);
      lcd.print(":");
      lcd.print(set_end1.min);


    }

  }

}
