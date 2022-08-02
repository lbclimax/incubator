int pos=0, maxPos=4;
void setting(){
  while(!digitalRead(ok))  delay(1000);
  lcd.clear();
  while(true){
    lcd.setCursor(0,0);
    lcd.print("FANYA MABADILIKO");
    lcd.setCursor(0,1);
    switch(pos){
      case 0:
      lcd.print("<<1.   JOTO   >>");
      break;
      case 1: 
      lcd.print("<<2.  UNYEVU  >>");
      break;
      case 2: 
      lcd.print("<3.MUDA-KUGEUZA>");
      break;
      case 3: 
      lcd.print("<KIPINDI-KUGEUZA");
      break;
      case 4: 
      lcd.print("<TOKA    SETAPU>");
      break;
    }
     
    

    if(!digitalRead(ok)){
      while(!digitalRead(ok))  delay(1000);
      switch(pos){
      case 0:
      changeTemp();
      break;
      case 1: 
      changeHum();
      break;
      case 2: 
      changeAutoTurnPeriod();
      break;
      case 3: 
      changeTurnPeriod();
      break;
      case 4: 
      break;
    }
      break;
    }
    else if(!digitalRead(left)){
      while(!digitalRead(left))  delay(1000);
      if(--pos<0)pos=maxPos;
 
  }
  else if(!digitalRead(right)){
      while(!digitalRead(right))  delay(1000);
      if(++pos>maxPos)pos=0;
      
  }

}}


void changeTemp(){
  lcd.clear();
  while(true){
    lcd.setCursor(0,0);
    lcd.print("  BADILI JOTO  ");
    lcd.setCursor(0,1);
    lcd.print("-< ");
    lcd.print(refTemp);
    lcd.write(5);
    lcd.print("C");
    lcd.print(" >+");

    if(!digitalRead(ok)){
      while(!digitalRead(ok))  delay(1000);
      break;
    }
    if(!digitalRead(right)) refTemp=refTemp+0.1;
    if(!digitalRead(left)) refTemp=refTemp-0.1;
    delay(500);
  }
  setTemp(refTemp);

}

void changeAutoTurnPeriod(){
  lcd.clear();
  while(true){
    lcd.setCursor(0,0);
    lcd.print("*MUDA WA KUGEUZA");
    lcd.setCursor(0,1);
    lcd.print("-< ");
    lcd.print(autoTurnPeriod); 
    lcd.print(" sec");
    lcd.print("    >+");

    if(!digitalRead(ok)){
      while(!digitalRead(ok))  delay(1000);
      break;
    }
    if(!digitalRead(right)) autoTurnPeriod=autoTurnPeriod+1;
    if(!digitalRead(left)) autoTurnPeriod=autoTurnPeriod-1;
    delay(500);
  }
 setAutoTurnPeriod( autoTurnPeriod);

}


void changeTurnPeriod(){
  lcd.clear();
  while(true){
    lcd.setCursor(0,0);
    lcd.print("*KIPINDI KUGEUZA");
    lcd.setCursor(0,1);
    lcd.print("-< ");
    int hr= turnPeriod/60;
    lcd.print(hr);
    lcd.print(":");
    lcd.print(turnPeriod%60); 
    lcd.print("    >+");

    if(!digitalRead(ok)){
      while(!digitalRead(ok))  delay(1000);
      break;
    }
    if(!digitalRead(right)) turnPeriod=turnPeriod+1;
    if(!digitalRead(left)) turnPeriod=turnPeriod-1;
    delay(500);
  }
 setTurnPeriod( turnPeriod);

}

void changeHum(){
  lcd.clear();
  while(true){
    lcd.setCursor(0,0);
    lcd.print("  BADILI UNYEVU  ");
    lcd.setCursor(0,1);
    lcd.print("-< ");
    lcd.print(refHum);
    
    lcd.print("%");
    lcd.print(" >+");

    if(!digitalRead(ok)){
      while(!digitalRead(ok))  delay(1000);
      break;
    }
    if(!digitalRead(right)) refHum=refHum+1;
    if(!digitalRead(left))  refHum=refHum-1;
    delay(500);
  }
  setHum(refHum);

}
void setTemp(float temp){
  EEPROM.put(0,temp);
}

 float getTemp(){
  float val;
  EEPROM.get(0,val);
  
  if(isnan(val))return 37.5;
  else return val;
}

void setHum(float temp){
  EEPROM.put(20,temp);
}

float getHum(){
  float val;
  EEPROM.get(20,val);
  
  if(isnan(val))return 65;
  else return val;
}


void setAutoTurnPeriod(int period){
  EEPROM.put(40,period);
}

int getAutoTurnPeriod(){
  int val;
  EEPROM.get(40,val);
  
  if(isnan(val))return 60;
  else return val;
}
void setTurnPeriod(int period){
  EEPROM.put(60,period);
}

int getTurnPeriod(){
  int val;
  EEPROM.get(60,val);
  
  if(isnan(val))return 180;
  else return val;
}


void setTurnDirection(){
  EEPROM.put(80,autoTurnDirection);
}

bool getTurnDirection(){
  bool val;
  EEPROM.get(80,val);
  
  if(isnan(val))return false;
  else return val;
}
