void setEPROM()
{
  address = 0;
  EEPROM.put(address, set_start1.hour);
  address += sizeof(set_start1.hour);
  EEPROM.put(address, set_start1.min);
  address += sizeof(set_start1.min);
  EEPROM.put(address, set_end1.hour);
  address += sizeof(set_end1.hour);
  EEPROM.put(address, set_end1.min);
  address += sizeof(set_end1.min);

  EEPROM.put(address, checkDoor);
  address += sizeof(checkDoor);

  EEPROM.put(address, set_lux_start);
  address += sizeof(set_lux_start);
  EEPROM.put(address, set_lux_end);
  address += sizeof(set_lux_end);

  EEPROM.put(address, set_temp_start);
  address += sizeof(set_temp_start);
}
void getEPROM()
{
  address = 0;
  EEPROM.get(address, set_start1.hour);
  address += sizeof(set_start1.hour);
  EEPROM.get(address, set_start1.min);
  address += sizeof(set_start1.min);

  EEPROM.get(address, set_end1.hour);
  address += sizeof(set_end1.hour);
  EEPROM.get(address, set_end1.min);
  address += sizeof(set_end1.min);

  EEPROM.get(address, checkDoor);
  address += sizeof(checkDoor);

  EEPROM.get(address, set_lux_start);
  address += sizeof(set_lux_start);
  EEPROM.get(address, set_lux_end);
  address += sizeof(set_lux_end);
  EEPROM.get(address, set_temp_start);
  address += sizeof(set_temp_start);
}
