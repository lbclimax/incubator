void check(){
  counter();
  checkCondition();
  
}

void counter(){
  seconds++;
  displayTime++;
  if(autoTurn)autoTurnTime++;
  else autoTurnTime=0;
  if(manualTurn){
    manualTurnTime++;
  }
  else{
    manualTurnTime=0;
  }
  if(displayTime>=maxDisplayTime){
    displayTime=0;
  }
  if(seconds>=60){
    seconds=0;
    minutes++;
    if(!autoTurn)nextTurn++;
    if(minutes>=60){
      minutes=0;
      hours++;
      if(hours>=24){
        hours=0;
        days++;
      }
    }
  }
  
}



void checkCondition(){
  if(temperature <= refTemp) digitalWrite(relayTemp,1);
 else digitalWrite(relayTemp,0);

 if(humidity <= refHum) digitalWrite(relayHum,1);
 else digitalWrite(relayHum,0);
}


void turnMotor(bool direction){
  if(direction){
    digitalWrite(motorA,1);
    digitalWrite(motorB,0);
  }
  else{
    digitalWrite(motorA,0);
    digitalWrite(motorB,1);
  }
}


void turnMotorOff(){
  digitalWrite(motorA,0);
  digitalWrite(motorB,0);
}
