
void settime(int start ) {
  lcd.setCursor(3, 0);
  lcd.print((String)"SetTimeStart " + start);
  lcd.setCursor(3, 2);
  lcd.print((String)"SetTimeEnd " + start);




}
void setLux( ) {
  lcd.setCursor(0, 0);
  lcd.print("SetLux");
  lcd.setCursor(0, 2);
  lcd.print("To");



}
void settemp( ) {
  lcd.setCursor(0, 0);
  lcd.print("Set Temp");
  lcd.setCursor(4, 1);
  lcd.print((String)"  To  ");


}
void setstate( ) {
  lcd.setCursor(0, 0);
  lcd.print("0.Online");
  lcd.setCursor(0, 1);
  lcd.print("1.Manually");
  lcd.setCursor(4, 2);
  lcd.print("   ");


}
void mainmenu() {

  lcd.setCursor(3, 0);
  lcd.print("1 SET TIME 1 ");
  lcd.setCursor(3, 1);
  lcd.print("2 SET TIME 2 ");
  lcd.setCursor(3, 2);
  lcd.print("3 SET LUX ");
  lcd.setCursor(3, 3);
  lcd.print("4 SET TEMP");

}
