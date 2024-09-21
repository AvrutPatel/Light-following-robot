// #include<iostream>
// #include<ArduinoLowPower.h>
// #include<avr/power.h>
#include<avr/sleep.h>

/* global variables accessed from ISRs */
volatile bool sleepModeState = false, 
              chaseModeState = true;  //activating HIDING mode if "false"

/* constants used for Arduino pins */
           //inputs
const byte startStopBtnPin =  2,
           chaseHideBtnPin =  3,
           rghtPhotoResPin = A2,
           leftPhotoResPin = A3,
           //outputs
           driverEnablePin =  7,

           rghtMotorPin[] = { 4,  5}, //D4, D5
           leftMotorPin[] = {14, 15}; //A0, A1


void setup()
{
  /* output pins */
  pinMode(driverEnablePin, OUTPUT); //D7
  pinMode(LED_BUILTIN,     OUTPUT); //13
  
  pinMode(leftMotorPin[0], OUTPUT); //A0
  pinMode(leftMotorPin[1], OUTPUT); //A1
  pinMode(rghtMotorPin[0], OUTPUT); //D4
  pinMode(rghtMotorPin[1], OUTPUT); //D5
  
  /* input pins */
  pinMode(rghtPhotoResPin, INPUT_PULLUP); //activate the internal pull-up resistor
  pinMode(leftPhotoResPin, INPUT_PULLUP); //activate the internal pull-up resistor
  pinMode(startStopBtnPin, INPUT_PULLUP);
  pinMode(chaseHideBtnPin, INPUT_PULLUP);
  
  /* configuring external hardware interrupts */
  attachInterrupt(digitalPinToInterrupt(startStopBtnPin), startStopBtnPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(chaseHideBtnPin), chaseHideBtnReleased, RISING);
  
  Serial.begin(115200);
}

void loop()
{
  if(sleepModeState == false) //Start
  {
    signed rghtPhotoResVal = 1023 - analogRead(rghtPhotoResPin);
    signed leftPhotoResVal = 1023 - analogRead(leftPhotoResPin);
    signed photoResDiffVal = abs(leftPhotoResVal - rghtPhotoResVal);

    Serial.print("Left LDR: ");
    Serial.print(leftPhotoResVal);
    Serial.print("\tRight LDR: ");
    Serial.print(rghtPhotoResVal);
    Serial.print("\tLDR Diff: ");
    Serial.print(photoResDiffVal);
    Serial.print("\tMode: ");
    
    digitalWrite(driverEnablePin, HIGH);
    
    if (chaseModeState == false) //CHASING mode
    {
      Serial.print("CHASE");
      Serial.print("\tAction: ");
      
      if (photoResDiffVal <= 10 && leftPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        driveForward();
      }
      else if (photoResDiffVal > 10 && leftPhotoResVal > rghtPhotoResVal && leftPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        turnLeft();
      }
      else if (photoResDiffVal > 10 && rghtPhotoResVal > leftPhotoResVal && rghtPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        turnRight();
      }
      else
      {
        stop();
      }
    }
    else //HIDING mode
    {
      Serial.print("HIDE");
      Serial.print("\tAction: ");
      
      if(photoResDiffVal <= 10 && leftPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        driveBackward();
      }
      else if(photoResDiffVal > 10 && leftPhotoResVal > rghtPhotoResVal && leftPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        turnRightBackward();
      }
      else if(photoResDiffVal > 10 && rghtPhotoResVal > leftPhotoResVal && leftPhotoResVal > 800 && rghtPhotoResVal > 800)
      {
        turnLeftBackward();
      }
      else
      {
        stop();
      }
    }
  }
  else //Stop
  {
    digitalWrite(driverEnablePin, LOW);
    Serial.print("Sleeping...\n");
    //Sleep...
    goToSleep();
  }
}

void goToSleep()
{
  byte adcsra = ADCSRA;
  ADCSRA = 0;
  
  set_sleep_mode(SLEEP_MODE_IDLE);
  cli();
  sleep_enable();
  sleep_bod_disable();
  sei();
  sleep_cpu();
  sleep_disable();
  ADCSRA = adcsra;
}

//ISR#0
void startStopBtnPressed() 
{
  sleepModeState = !sleepModeState;
}
//ISR#1
void chaseHideBtnReleased() 
{
  chaseModeState = !chaseModeState;
}

void stop()
{
  digitalWrite(leftMotorPin[1], LOW);
  digitalWrite(leftMotorPin[0], LOW);
  digitalWrite(rghtMotorPin[1], LOW);
  digitalWrite(rghtMotorPin[0], LOW);

  Serial.println("Stop");
}

void driveForward()
{
  digitalWrite(leftMotorPin[1],  LOW);
  digitalWrite(leftMotorPin[0], HIGH);
  digitalWrite(rghtMotorPin[1], HIGH);
  digitalWrite(rghtMotorPin[0],  LOW);
  
  Serial.println("Forward");
}

void driveBackward()
{  
  digitalWrite(leftMotorPin[1], HIGH);
  digitalWrite(leftMotorPin[0],  LOW);
  digitalWrite(rghtMotorPin[1],  LOW);
  digitalWrite(rghtMotorPin[0], HIGH);

  Serial.println("Backward");
}

void turnRight()
{
  digitalWrite(leftMotorPin[1],  LOW);
  digitalWrite(leftMotorPin[0], HIGH);
  digitalWrite(rghtMotorPin[1],  LOW);
  digitalWrite(rghtMotorPin[0],  LOW);

  Serial.println("Right");
}

void turnRightBackward()
{ 
  digitalWrite(leftMotorPin[1], HIGH);
  digitalWrite(leftMotorPin[0],  LOW);
  digitalWrite(rghtMotorPin[1],  LOW);
  digitalWrite(rghtMotorPin[0],  LOW);

  Serial.println("Right Backward");
}

void turnLeft()
{ 
  digitalWrite(leftMotorPin[1],  LOW);
  digitalWrite(leftMotorPin[0],  LOW);
  digitalWrite(rghtMotorPin[1], HIGH);
  digitalWrite(rghtMotorPin[0],  LOW);

  Serial.println("Left");
}

void turnLeftBackward()
{
  digitalWrite(leftMotorPin[1],  LOW);
  digitalWrite(leftMotorPin[0],  LOW);
  digitalWrite(rghtMotorPin[1],  LOW);
  digitalWrite(rghtMotorPin[0], HIGH);

  Serial.println("Left Backward");
}

void turnCounterclockwise()
{ 
  digitalWrite(leftMotorPin[1], HIGH);
  digitalWrite(leftMotorPin[0],  LOW);
  digitalWrite(rghtMotorPin[1], HIGH);
  digitalWrite(rghtMotorPin[0],  LOW);

  Serial.println("Counterclockwise");
}

void turnClockwise()
{
  digitalWrite(leftMotorPin[1],  LOW);
  digitalWrite(leftMotorPin[0], HIGH);
  digitalWrite(rghtMotorPin[1],  LOW);
  digitalWrite(rghtMotorPin[0], HIGH);

  Serial.println("Clockwise");
}
