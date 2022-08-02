
#include <MsTimer2.h>

#include <EEPROM.h>

#include <DHT.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(11,10,9,8,7,6);

DHT dht(12,DHT11);

const int ok = 2,left =0, right = 1,relayTemp = A4 ,relayHum = A5,motorA=4,motorB=5;
bool lastLeftPos=false,lastRightPos=false,manualTurn=false ,autoTurn=false ,autoTurnDirection=false;
int leftPressCount=0,rightPressCount=0;
int seconds=0,minutes=0,hours=0,days=0,displayTime=0,maxDisplayTime=10,manualTurnTime=0,turnPeriod=1,nextTurn=0,autoTurnTime=0,autoTurnPeriod=30;

float temperature ,humidity ,refTemp,refHum;
// make some custom characters:
byte degree[8] = {
  B11110,
  B10010,
  B10010,
  B11110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  pinMode(ok,INPUT_PULLUP);
  pinMode(left,INPUT_PULLUP);
  pinMode(right,INPUT_PULLUP);

  pinMode(relayTemp,OUTPUT);
  pinMode(relayHum,OUTPUT);
  pinMode(motorA,OUTPUT);
  pinMode(motorB,OUTPUT);
  
  lcd.createChar(5, degree);  
  lcd.begin(16,2);
  refTemp= getTemp();
  refHum=getHum();
  autoTurnPeriod=getAutoTurnPeriod();
  turnPeriod=getTurnPeriod();
  autoTurnDirection=getTurnDirection();
  dht.begin();
   MsTimer2::set(1000, check); // 500ms period
  MsTimer2::start();
  turnMotorOff();
  
 }

void loop() {
  temperature = dht.readTemperature();
  humidity =  dht.readHumidity();
 if(autoTurn){
   lcd.setCursor(0,0);
   lcd.print("AUTO   TURNING    ");
   lcd.setCursor(0,1);
   if(autoTurnDirection)lcd.print(" TURN UP :");
   else lcd.print("TURN DOWN :");
   lcd.print(autoTurnTime);
   lcd.print("           ");
   
   
 }
 else if(displayTime<5) displayHome();
 else displayTimes();
//lcd.setCursor(0,0);
 if(!digitalRead(ok)) setting();
// lcd.print ("PRESSED                    ");
// else lcd.print (" NOT PRESSED                    ");

if(!digitalRead(left)){
  leftPressCount=0;
  while(!digitalRead(left)){
    lcd.setCursor(0,0);
    lcd.print("GEUZA MAYAI JUU!");
    lcd.setCursor(0,1);
    
    
    if(leftPressCount<2){
      leftPressCount++;
      lcd.print("SUBIRI   ......!");
      delay(1000);
    }
    else{
      turnMotor(true);
      manualTurn=true;
      lcd.print("INAGEUZA: ");
      lcd.print(manualTurnTime);
      lcd.print(" sec  ");
      
    }
  }

  turnMotorOff();
  manualTurn=false;
  autoTurnDirection=false;
  setTurnDirection();
  if(autoTurn){
    autoTurn=false;
    nextTurn=0;
  }
}

if(!digitalRead(right)){
  rightPressCount=0;
  while(!digitalRead(right)){
    lcd.setCursor(0,0);
    lcd.print("GEUZA      CHINI");
    lcd.setCursor(0,1);
    
    
    if(rightPressCount<2){
      rightPressCount++;
      lcd.print("SUBIRI   ......!");
      delay(1000);
    }
    else{
      turnMotor(false);
      manualTurn=true;
      lcd.print("INAGEUZA: ");
      lcd.print(manualTurnTime);
      lcd.print(" sec  ");
      
    }
  }

  turnMotorOff();
  manualTurn=false;
   autoTurnDirection=true;
    setTurnDirection();
  if(autoTurn){
    autoTurn=false;
    nextTurn=0;
  }
}
if(nextTurn>=turnPeriod){
  autoTurn=true;
  turnMotor     (autoTurnDirection);
}

if(autoTurn && autoTurnTime>=autoTurnPeriod){
  autoTurn=false;
  turnMotorOff();
  nextTurn=0;
  autoTurnDirection=!autoTurnDirection;
   setTurnDirection();
}

}
