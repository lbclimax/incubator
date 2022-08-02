void displayHome(){
  lcd.setCursor(0,0);

 lcd.print("JOTO   :");
 lcd.print(temperature);
 lcd.write(5);
 lcd.print("C                    ");
 lcd.setCursor(0,1);
 lcd.print("UNYEVU : ");
  lcd.print(humidity);
  lcd.print("%          ");
}


void displayTimes(){
  lcd.setCursor(0,0);
  lcd.print("SIKU :  " );
  lcd.print(days);
  lcd.print("                      ");
 lcd.setCursor(0,1);
 lcd.print("MUDA :  ");
 lcd.print(hours);
 lcd.print(":");
 lcd.print(minutes);
 lcd.print(":");
 lcd.print(seconds);
 lcd.print("                      ");
}
